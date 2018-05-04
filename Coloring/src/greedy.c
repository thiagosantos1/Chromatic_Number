
#include <findcolor.h>

int greedycoloring(GRAPH *op)
{
  int *used;
  int c,n,u,v;
  int ncolors;
  int maxcolorused=0,vert_ngbr;

  n = op->order;
  ncolors  = op->maxdegree;

  used = malloc(ncolors * sizeof(int));

  op->coloring[0] = 0; // color the first one already
  for(v=1;v<n;v++)              
    op->coloring[v] = NOCOLOR; // not yet colored

  for(v=1;v<n;v++){
    // initialize to 0, all colors
    memset(used,0,ncolors*sizeof(int));

//  for each neighbor of V, set which color is not available, by checking which its neighbors are using
    for(u=0; u<op->deg[v]; u++){
      vert_ngbr = op->adj_list[v].nbrs[u];
      if(op->coloring[vert_ngbr] != NOCOLOR)
        used[op->coloring[vert_ngbr]] = 1;
    }  

//  Then, find a color that is not used to assign for that vertex
    for(c=0;c<ncolors;c++)
      if(!used[c])
        break;
    op->coloring[v] = c;
    maxcolorused = c > maxcolorused ? c:maxcolorused;
  }

  free(used);
  return maxcolorused + 1;
}
