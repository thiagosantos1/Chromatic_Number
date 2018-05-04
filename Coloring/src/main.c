
#include <findcolor.h>

#define PRINT_RESULTS 

void display_coloring(int colors[], int n);

int main(int argc, char *argv[])
{ 
  USER_PARAMS inpar;
  GRAPH outpar;
  int k, rv, nused=0;

  if(argc < 3){
    fprintf(stderr, "Usage <Order> & <filename> %s\n",argv[0]);
    exit(0);
  }
  printf("\n");
  inpar.order = atoi(argv[1]);
  inpar.filename = strdup(argv[2]);
  // paramters for the rand search
  inpar.give_up_time = 20;
  inpar.num_to_recolor = inpar.order * 0.2; // 20% percent
  inpar.max_give_ups = 200; 
  rv = makegraph(&outpar, &inpar);
  if(rv < 0)
    exit(0);

  k = bipartite(&outpar);
  if(k<1)
    fprintf(stderr,"Graph is not bipartite, going to next step of verification\n");
  else{
    fprintf(stderr,"Graph is bipartite. Chromatic number = 2 \n");
    outpar.chromatic = 2;
    #ifdef PRINT_RESULTS 
      display_coloring(outpar.coloring, outpar.order);
    #endif
    exit(0);
  }

  if(outpar.is_graph_connected <1){
    fprintf(stderr,"Graph is not connected. Please, provide a connected graph, or make a new graph for each disconnected\n");
    exit(0);
  }

  nused = greedycoloring(&outpar);
  fprintf(stderr,"greedycoloring used: %d colors\n",nused);
  #ifdef PRINT_RESULTS 
    display_coloring(outpar.coloring, outpar.order);
  #endif

  if(nused == outpar.maxdegree +1){ // prove by theory

    if(outpar.maxdegree == 2)
      fprintf(stderr,"Graph with odd cycles! Chromatic number is %d\n",3); 
    else
      fprintf(stderr,"This is a complete graph! Chromatic number is %d\n",nused);
    outpar.chromatic = nused;

    #ifdef PRINT_RESULTS 
      display_coloring(outpar.coloring, outpar.order);
    #endif

    exit(0);
  }else if(nused > outpar.maxdegree  +1){
    fprintf(stderr,"Somethig is wrong. Number of colors used can't be > maxdegree +1\n");
    exit(0);
  }
  else{
    fprintf(stderr,"Going to next step to find the Chromatic number......\n");
  }

  /* rand search */
  outpar.mincolors = nused;
  fprintf(stderr, "randomize search have started.....\n" );
  rand_search(&outpar,&inpar);
  fprintf(stderr, "randomize search is done.....\n" );
  #ifdef PRINT_RESULTS 
    fprintf(stderr, "\n\t\t*** Results ***\n");
    fprintf(stderr, "Chromatic guessed: %d\n",outpar.mincolors);
    fprintf(stderr, "\t\t*** Coloring ***\n");
    display_coloring(outpar.coloring, outpar.order);
  #endif

  int new_try = outpar.mincolors -1;
  fprintf(stderr, "exhaust search have started for %d colors.....\n", new_try );
  exh_search(&outpar,&inpar);
  fprintf(stderr, "exhaust search is done.....\n" );

  #ifdef PRINT_RESULTS 
    fprintf(stderr, "\n\t\t*** Final Results ***\n");
    fprintf(stderr, "Chromatic number: %d\n",outpar.mincolors);
    fprintf(stderr, "\t\t*** Coloring ***\n");
    display_coloring(outpar.coloring, outpar.order);
  #endif
  
}

void display_coloring(int colors[], int n)
{
  for (int i = 0; i < n; ++i)
    fprintf(stderr, "%d ",colors[i]);
  printf("\n");
}

