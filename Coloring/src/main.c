
#include <findcolor.h>

#define PRINT_RESULTS

/*
 * simple test program for the graph coloring library
 */

int main(int argc, char *argv[])
{ 
  USER_PARAMS inpar;
  GRAPH outpar;
  int i, k, rv, nused;
  int rand_search_guess;

  if(argc < 3){
    fprintf(stderr, "Usage <Order> & <filename> %s\n",argv[0]);
    exit(0);
  }
  inpar.order = atoi(argv[1]);
  inpar.filename = strdup(argv[2]);
  rv = makegraph(&outpar, &inpar);
  if(rv < 0)
    exit(0);

  k = bipartite(&outpar);
  if(k<1)
    fprintf(stderr,"Graph is not bipartite, going to next step of verification\n");
  else{
    fprintf(stderr,"Graph is bipartite. Chromatic number = 2 \n");

    #ifdef PRINT_RESULTS 
      for(i=0;i<inpar.order;i++)
        fprintf(stderr,"%3d",outpar.coloring[i]);
      fprintf(stderr,"\n");
    #endif
    exit(0);
  }

  if(outpar.is_graph_connected <1){
    fprintf(stderr,"Graph is not connected. Please, provide a connected graph, or make a new graph for each disconnected\n");
    exit(0);
  }

  nused = greedycoloring(&outpar);
  fprintf(stderr,"greedycoloring used: %d colors\n",nused);

  if(nused == outpar.maxdegree +1){ // prove by theory

    if(outpar.maxdegree == 2)
      fprintf(stderr,"Graph with odd cycles! Chromatic number is %d\n",nused);
    else
      fprintf(stderr,"This is a complete graph! Chromatic number is %d\n",nused);

    #ifdef PRINT_RESULTS 
      for(i=0;i<inpar.order;i++)
        fprintf(stderr,"%3d",outpar.coloring[i]);
      fprintf(stderr,"\n");
    #endif

    exit(0);
  }else if(nused > outpar.maxdegree  +1){
    fprintf(stderr,"Somethig is wrong. Number of colors used can't be > maxdegree +1\n");
    exit(0);
  }

  if(outpar.order > outpar.minimum_order_rand){ // if order is greather than the minimum required, do a rand search


  }

}



