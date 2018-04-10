
#include <findcolor.h>

/*
 * find largest degree for all vertices
 */
int maxdegree(GRAPH *op)
{
  int d,u,maxd;   // u and v are vertices, maxd is maxdegree

  maxd = 0;
  for(u = 0 ; u < op->n ; u++){
    d = op->deg[u];
    if(d > maxd)
      maxd = d;
  }
  return maxd;
}

