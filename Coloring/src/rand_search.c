#include <findcolor.h>

//#define MULT_THREAD

pthread_mutex_t mut;

void *rand_search_coloring_th(void *ptr);

void rand_search_coloring(GRAPH *op,USER_PARAMS *ip);
void randperm(int sig[], int n);
void shuffle(int sig[], int n);
void display_colors(int colors[], int n);
int score(int color[], GRAPH *op);
int bestcolor(int v, int ncolors, int color[],GRAPH *op);
int pickmin_color_used(int list[], int nc);

void rand_search(GRAPH *op,USER_PARAMS *ip)
{
  #ifdef MULT_THREAD
    int i;
    pthread_t th[NT];   // data structures that pthread functions use
    int myid[NT];
    /* starting threads */
    pthread_mutex_init(&mut, 0);

    for(i=0;i<NT;i++)
      myid[i] = i + 2;

    for(i=0;i<NT;i++)
      pthread_create(&th[i], 0, rand_search_coloring, &myid[i]);
    
    for(;;){
      sleep(1);
      pthread_mutex_lock(&mut);
        fprintf(stderr,"%d\n", op->mincolors);
      pthread_mutex_unlock(&mut);
    }
    for(i=0;i<NT;i++)
      pthread_join(th[i], 0);
  #else
    rand_search_coloring(op,ip);
  #endif

}

void rand_search_coloring(GRAPH *op,USER_PARAMS *ip)
{
  int sigma[op->order]; // used to rand shuffle the vertices(to don't become bias)
  int color_copy[op->order]; // a copy of the best coloring we have so far
  int u,i,newscore,best,best_color;
  int ncolors,trials,lastimproved,giveup;
  int order = op->order;

  srandom(3);
  // make a copy of coloring
  memcpy(color_copy, op->coloring, order * sizeof(int));

  // set num of available colors to min colors found in greedy color
  ncolors = op->mincolors;
  randperm(sigma,order);

  // execute the loop until there's no improve anymore, for a while of predifined time 
  for(;;){
    --ncolors; // try for one less color
    giveup = 0; // reset give up
    for(i=0;i<order;i++){
      if(color_copy[i] == ncolors){
        color_copy[i] = (int)RND(ncolors); //if color of vertex is = to the color we eliminate
                                // assign a new & rand one
      }
    }
    // save how many bad edges(conflicts) in the graph. Goal is to minimize this score
    best = score(color_copy,op);
    trials = lastimproved = 0;

    // while best is not zero(still have bad edges)
    // and the giveup is smaller that the maxim set. Avoid spending forever
    while(best >0 && giveup < ip->max_give_ups){

      trials++;
      shuffle(sigma,order);
      for(i=0;i<order;i++){
        u = sigma[i];
        best_color = bestcolor(u, ncolors, color_copy,op);
        color_copy[u] = best_color;
      }

      newscore = score(color_copy,op);
      // have improved the number of bad edges
      if(newscore < best){
        lastimproved = trials;
        best = newscore;
        giveup = 0;
      }else {
        // if did not improved for a while, we should try a different rand set of variables and colors
        if((trials - lastimproved) > ip->give_up_time){
          lastimproved = trials;
          // let's recolor some rand vertices with rand colors
          for(i = 0 ; i < ip->num_to_recolor ; i++)
            color_copy[RND(order)] = (int)RND(ncolors);
          // set that we are trying a diferent combination
          giveup++;
        }
      }
    }

    // it means we exit the while because did not improved for a while
    if(best >0)
      break;
    else{ // it means we succed with coloring with ncolors -1
      if(ncolors < op->mincolors){
        // save best found
        op->mincolors = ncolors;
        // copy the coloring got, to the original coloring set
        memcpy(op->coloring, color_copy, order * sizeof(int));
      }

    }
  }

}

void randperm(int sig[], int n)
{
  int i;

  for(i=0;i<n;i++)
    sig[i] = i;
  shuffle(sig, n);
}

void shuffle(int sig[], int n)
{
  int i,j,t;

  for(i=n-1;i>1;i--){
    j = RND(i);
    if(i != j){
      t = sig[i]; 
      sig[i] = sig[j]; 
      sig[j] = t;
    }
  }
}

void display_colors(int colors[], int n)
{
  for (int i = 0; i < n; ++i)
    fprintf(stderr, "%d ",colors[i]);
  printf("\n");
}

int score(int color[], GRAPH *op)
{
  int i,j,k=0;

  for(i=0;i<op->order;i++){
    for(j=0;j<op->order;j++){
      if(i < j &&  op->a[i][j]== 1){ // to calculate just once the edge as bad edge
        if(color[i] == color[j])
          k++;
      }
    }
  }

  return k;
}

/*
 * which color assigned v gives the fewest bad edges (both ends same color)
 */
int bestcolor(int v, int ncolors, int color[],GRAPH *op)
{
  int u;
  int timesused[ncolors];

  memset(timesused, 0, ncolors*sizeof(int));
  for(u=0;u<op->order;u++)
    if(op->a[u][v] >0)
      timesused[color[u]]++;

  return pickmin_color_used(timesused, ncolors);
}

/*
 * find index of minimum element. A color that has not being used much
 */
int pickmin_color_used(int list[], int nc)
{
  int i,bc[nc],m,n;
//
// bc is the list of best colors
//
  m = list[0];   // min value for the array, so far
  bc[0] = 0;     // which element achieves that minimum
  n = 1;         // how many elements have achieved the minumum

  for(i=1;i<nc;++i){
    if(list[i] < m){
      m = list[i];
      n = 1;
      bc[0] = i;
    } else if(list[i] == m){
      bc[n++] = i;
    }
  }
  if(n == 0) {
    fprintf(stderr,"Error in pickmin_color_used\n");
    exit(0);
  }
  if(n == 1)
    return(bc[0]);
  else
    return(bc[RND(n)]);
}