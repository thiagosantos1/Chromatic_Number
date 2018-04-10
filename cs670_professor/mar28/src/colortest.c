
#include <findcolor.h>

/*
 * simple test program for the graph coloring library
 */

int main(int argc, char *argv[])
{
  USER_PARAMS inpar;
  GRAPH outpar;
  int i, k, rv;

  inpar.n = atoi(argv[1]);
  inpar.filename = strdup(argv[2]);
  rv = makegraph(&outpar, &inpar);
  if(rv < 0)
    exit(0);
  k = greedycoloring(&outpar);
  printf("greedycoloring: %d\n",k);
  for(i=0;i<inpar.n;i++)
    printf("%3d",outpar.coloring[i]);
  printf("\n");
  k = bipartite(&outpar);
  printf("bipartite coloring: %d\n",k);
  for(i=0;i<inpar.n;i++)
    printf("%3d",outpar.coloring[i]);
  printf("\n");
}
