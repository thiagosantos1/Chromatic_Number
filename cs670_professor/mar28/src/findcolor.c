
#include <findcolor.h>

pthread_mutex_t mut;

/* best number of colors found, and best coloring */

int randcolor(GRAPH *gp)
{
  int i,j,k,n;
/*
 * start with random or greedy
 */

  n = op->n;
  for(i=0;i<n;i++)
    op->coloring[i] = random() % 10;
  return 10;
}
