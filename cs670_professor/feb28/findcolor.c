
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#define NT       48    // number of threads

#define NOCOLOR  -1

#define GIVEUPTIME     5
#define NUMTORECOLOR   9 
#define MAXGIVEUPS   100 

#define DEBUG

#define RND(X)   (lrand48() % (X))

typedef
  unsigned char
uchar;

pthread_mutex_t mut;

/* best number of colors found, and best coloring */

int mincolors;
int *bestcoloring;

unsigned char **a;
int *elist;
int N, nedges;

int make_elist();
void greedycoloring(int color[], int ncolors);
void *findcoloring(void *ptr);
void makegraph(FILE *fd);
int maxdegree();

int main(int argc, char *argv[])
{
  FILE *fd;
  int i,j,k;
  pthread_t th[NT];   // data structures that pthread functions use
  int myid[NT];
  int maxd;

  if(argc < 3){
    fprintf(stderr,"usage: %s N matrix\n",argv[0]);
    exit(0);
  }
  N = atoi(argv[1]);
  fd = fopen(argv[2],"r");
  if(fd == NULL){
    fprintf(stderr,"cannot open %s\n", argv[2]);
    exit(0);
  }
  makegraph(fd);

/* create initial greedy coloring */
  maxd = maxdegree();
  mincolors = maxd + 1;
  greedycoloring(bestcoloring, mincolors);

/* starting the threads */

  pthread_mutex_init(&mut, 0);

  for(i=0;i<NT;i++)
    myid[i] = i + 2;

  for(i=0;i<NT;i++)
    pthread_create(&th[i], 0, findcoloring, &myid[i]);
  
  for(;;){
    sleep(1);
    pthread_mutex_lock(&mut);
      fprintf(stderr,"%d\n", mincolors);
    pthread_mutex_unlock(&mut);
  }

  for(i=0;i<NT;i++)
    pthread_join(th[i], 0);
}

void makegraph(FILE *fd)
{
  int i,j,k;

// allocate space for matrix

  a = malloc(N*sizeof(uchar *));
  for(i=0;i<N;i++)
    a[i] = malloc(N*sizeof(uchar));
  nedges = 0;
  for(i=0;i<N;i++)
    for(j=0;j<N;j++){
      fscanf(fd,"%1d",&k);
      a[i][j] = k;
      if(i < j && k == 1)
        nedges++;
    }
  fclose(fd);

// allocate space for edgelist

  elist = malloc(2 * nedges * sizeof(int));
  make_elist();

// allocate space for edgelist
  bestcoloring = malloc(N * sizeof(int));
}
/*
 * since we are using max deg + 1 colors, greedy coloring cannot fail
 */
void greedycoloring(int color[], int ncolors)
{
  int used[ncolors];
  int i,c,u,v;

  color[0] = 0;
  for(v=1;v<N;v++)              // not yet colored
    color[v] = NOCOLOR;

  for(v=1;v<N;v++){
//
// set the count to 0 for each color
//
    memset(used,0,ncolors*sizeof(int));
//
//  count how many times each color is used on the neighbors of v
//
    for(u=0;u<N;u++)
      if(a[u][v] && color[u] != NOCOLOR)
        used[color[u]] = 1;
//
//  find a color that is not used
//
    for(c=0;c<ncolors;c++)
      if(!used[c])
        break;
    if(c >= ncolors){
      fprintf(stderr,"impossible? all colors are used at vertex %d\n", v);
      exit(0);
    }
    color[v] = c;
  }
}
/*
 * count the number of neighbors of u
 */
int getdegree(int u)
{
  int v,count;

  for(v = count = 0; v < N ; v++)
    if(u != v && a[v][u])
      count++;
  return count;
}
/*
 * find largest degree for all vertices
 */
int maxdegree()
{
  int d,u,maxd;   // u and v are vertices, maxd is maxdegree

  maxd = 0;
  for(u=0;u<N;u++){
    d = getdegree(u);
    if(d > maxd)
      maxd = d;
  }
  return maxd;
}
/*
 * convert matrix to edge list
 */
int make_elist()
{
  int i,j,k;

  k = 0;
  for(i=0;i<N-1;i++)
    for(j=i+1;j<N;j++)
      if(a[i][j] == 1){
        elist[k++] = i;
        elist[k++] = j;
      }
  if(k != 2*nedges){
    fprintf(stderr,"wrong number of edges: %d != %d\n", k/2, nedges);
    exit(0);
  }
}
/*
 * find index of minimum element in any integer array
 */
int pickmin(int list[], int nc)
{
  int i,bc[nc],m,n,d;
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
    fprintf(stderr,"pickmin: n = %d\n", n);
    exit(0);
  }
  if(n == 1)
    return(bc[0]);
  else
    return(bc[RND(n)]);
}
/*
 * which color assigned v gives the fewest bad edges (both ends same color)
 */
void bestcolor(int v, int ncolors, int color[])
{
  int u,i,j,k;
  int timesused[ncolors];

  memset(timesused, 0, ncolors*sizeof(int));
  for(u=0;u<N;u++)
    if(a[u][v])
      timesused[color[u]]++;
  k = pickmin(timesused, ncolors);
  color[v] = k;
}
/*
 * total number of bad edges in the graph
 */
int score(int color[])
{
  int i,j,k;

  k = 0;
  for(i=0;i<2*nedges;i+=2)
    if(color[elist[i]] == color[elist[i+1]])
        k++;
  return k;
}

int shuffle(int sig[], int n)
{
  int i,j,k,t;

  for(i=N-1;i>1;i--){
    j = RND(i);
    if(i != j){
      t = sig[i]; sig[i] = sig[j]; sig[j] = t;
    }
  }
}
int randperm(int sig[], int n)
{
  int i;

  for(i=0;i<N;i++)
    sig[i] = i;
  shuffle(sig, n);
}
// convention *p means I malloc-ed, p[] means someone else did

void *findcoloring(void *myidptr)
{
  int me;
  int sigma[N];
  int count[N];
  int color[N];
  int u,i,c,newscore,best,maxd;
  int ncolors,trials,lastimproved,giveup;

  me = * (int *) myidptr;
  srandom(me);
  pthread_mutex_lock(&mut);         // this reader code
    for(i=0;i<N;i++)
      color[i] = bestcoloring[i];
    ncolors = mincolors;
  pthread_mutex_unlock(&mut);

  randperm(sigma,N);
  for(;;){                          // once for each value of ncolors
    --ncolors;
    giveup = 0;
    for(u=0;u<N;u++)
      if(color[u] == ncolors)
        color[u] = RND(ncolors);
    best = score(color);
    trials = lastimproved = 0;
    while(best > 0){
//
//    reader code needs to be added here, but not every look,
//    this code blocks writers, but as soon as a writer shows
//    up, no new readers can enter until the writer is done.
//
//    one method is to use a time, and check independently
//       lasttimedcheck would be time(0) value when this thread
//       last checked the best solutions
//
//    second method, the main thread signals the threads to check
//       main thread would be checking the best solution, and whenever
//       it changes, signals everyone body (else) to check it
//
      trials++;
      shuffle(sigma,N);
      for(i=0;i<N;i++){
        u = sigma[i];
        bestcolor(u, ncolors, color);
      }
      newscore = score(color);
      if(newscore < best){
        lastimproved = trials;
        best = newscore;
        giveup = 0;
      } else {
        if((trials - lastimproved) > GIVEUPTIME){
          lastimproved = trials;
          for(i = 0 ; i < NUMTORECOLOR ; i++)
            color[RND(N)] = lrand48() % ncolors;
          giveup++;
        }
      }
    }
    pthread_mutex_lock(&mut);           // writer code
      if(ncolors < mincolors){
        mincolors = ncolors;
        memcpy(bestcoloring, color, N*sizeof(int));
        fprintf(stderr,"thread %d succeeded with %d colors\n", me, ncolors);
      } else {
        ncolors = mincolors;
      }
    pthread_mutex_unlock(&mut);
  }
  pthread_exit(0);
}
