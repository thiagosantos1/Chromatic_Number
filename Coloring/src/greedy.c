
#include <findcolor.h>

int greedycoloring(GRAPH *op)
{
  int *used;
  int c,n,u,v;
  int ncolors;
  int maxcolorused;

  n = op->n;
  ncolors = maxdegree(op);

  used = malloc(ncolors * sizeof(uchar));

  op->coloring[0] = 0;
  for(v=1;v<n;v++)              // not yet colored
    op->coloring[v] = NOCOLOR;

  for(v=1;v<n;v++){
//
// set the count to 0 for each color
//
    memset(used,0,ncolors*sizeof(int));
//
//  count how many times each color is used on the neighbors of v
//
    for(u=0;u<n;u++)
      if(op->a[u][v] && op->coloring[u] != NOCOLOR)
        used[op->coloring[u]] = 1;
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
    op->coloring[v] = c;
    if(c > maxcolorused) maxcolorused = c;
  }
  free(used);
  return maxcolorused + 1;
}

