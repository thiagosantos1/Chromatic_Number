
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N     216
#define COLS ((N+7)/8)

#define  ARE_ADJACENT(X,Y)  (amat[(X)][(Y)>>3] & (1 << ((Y) & 0x7)))
#define  ADD_ARC(X,Y)        amat[(X)][(Y)>>3] |= (1 << ((Y) & 0x7))

#define CHUNK   4

typedef
  unsigned char
uchar;

typedef struct {
  int deg;                // degree of vertex is the number of neighbors
  int size;               // how many list items have been allocated
  int *nbrs;              // list of neighbors
} ALIST;

ALIST alist[N];

uchar amat[N][COLS];

void update_alist(int u, int v);

int main()
{
  int i,j,u,v,tmp;

  for(i=0;i<N;i++)
    for(j=0;j<COLS;j++)
      amat[i][j] = 0;
  for(i=0;i<N;i++)
    alist[i].deg  = 0;
    alist[i].size = 0;
    alist[i].nbrs = 0;  // null pointer
  }
  while(scanf("%d %d", &u, &v) == 2){
    ADD_ARC(u,v);
    ADD_ARC(v,u);
    update_alist(u,v);
    update_alist(v,u);
  }
  for(i=0;i<N;i++){
    printf("%3d", i);
    for(j=0;j<N;j++)
      if(ARE_ADJACENT(i,j))
        printf("%6d", j);
    printf("\n");
  }
}
void update_alist(int u, int v)
{
  int tmp;

  if(alist[u].deg >= alist[u].size){
    if(alist[u].size == 0){
      alist[u].size = CHUNK;
      alist[u].nbrs = malloc(CHUNK * sizeof(int));
    } else {
      alist[u].size += CHUNK;
      tmp = alist[u].size;
      alist[u].nbrs = realloc(alist[u].nbrs, tmp * sizeof(int));
    }
  }
}
