
#include <findcolor.h>

int makegraph(GRAPH *op, USER_PARAMS *ip)
{
  int i,j,k;
  int N, nedges;
  FILE *fd;

  fd = fopen(ip->filename,"r");
  if(!fd)
    return -1;
  N = op->n = ip->n;

// allocate space for matrix

  op->a   = malloc(N*sizeof(uchar *));
  op->deg = malloc(N*sizeof(int));
  memset(op->deg, 0, N * sizeof(int));
  for(i=0;i<N;i++)
    op->a[i] = malloc(N*sizeof(uchar));

// read matrix

  nedges = 0;
  for(i=0;i<N;i++)
    for(j=0;j<N;j++){
      fscanf(fd,"%1d",&k);  // check this, for invalid data file 
      op->a[i][j] = k;
      if(i < j && k == 1){  // add each edge once
        op->deg[i]++;
        op->deg[j]++;
        nedges++;
      }
    }
  fclose(fd);

// allocate space for edgelist and coloring

  op->elist = malloc(2 * nedges * sizeof(int));
  op->m = nedges;
  op->coloring = malloc(N * sizeof(int));

  return 0;

}

