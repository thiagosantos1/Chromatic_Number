
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

typedef
  unsigned char
uchar;

typedef struct {
  int wgt;
  int val;
  int val2end;  // sum of values from this item to last item
  uchar used;
  uchar best;
} ITEM;

ITEM *list;
 
int *callcount;

int printlist(ITEM *li, int n);
int countitems(FILE *fd);
int readitems(FILE *fd, int n, ITEM *li);
int dfs(int depth, int n, int currval, int currwgt, int maxwgt, ITEM *li);

int main(int argc, char *argv[])
{
  FILE *fd;
  int i,j,n,tar;

  if(argc != 3){
    fprintf(stderr,"usage: %s problemFile target\n", argv[0]);
    exit(0);
  }
  fd = fopen(argv[1],"r");
  tar = atoi(argv[2]);
  if(fd == NULL){
    fprintf(stderr,"unable to open %s\n", argv[1]);
    exit(0);
  }
  n = countitems(fd);
  callcount = malloc((n + 1) * sizeof(int));
  memset(callcount, 0, (n + 1) * sizeof(int));
  list = malloc(n * sizeof(ITEM));
  readitems(fd,n,list);
  j = 0;
  for(i=n-1;i>=0;--i){
    j += list[i].val;
    list[i].val2end = j;
  }
  dfs(0, n, 0, 0, tar, list);
  for(i=0;i<=n;i++)
    fprintf(stderr,"%2d%12d\n", i, callcount[i]);
  printf("%d\n",printlist(list,n));
}
int countitems(FILE *fd)
{
  int n,x,y;

  n = 0;
  while(fscanf(fd,"%d %d", &x, &y) == 2)
    n++;
  fseek(fd, 0, SEEK_SET);
  return n;
}

int readitems(FILE *fd, int n, ITEM *li)
{
  int m,x,y;

  m = 0;
  while(fscanf(fd,"%d %d", &x, &y) == 2){
    li[m].wgt = x;
    li[m].val = y;
    li[m].used = 0;  // false
    m++;
  }
  return (m == n);
}
int printlist(ITEM *li, int n)
{
  int i, tw, tv;
  
  tw = tv = 0;
  for(i=0;i<n;i++)
    if(li[i].best){
      tw += li[i].wgt;
      tv += li[i].val;
      fprintf(stderr,"%3d%6d%6d\n",i,li[i].wgt,li[i].val);
    }
  fprintf(stderr,"---------------\n");
  fprintf(stderr,"%9d%6d\n\n",tw,tv);
  return tw;
}
int dfs(int depth, int n, int currval, int currwgt, int maxwgt, ITEM *li)
{
  static int maxval = 0;
  int i;

  callcount[depth]++;
  if(currwgt > maxwgt)
    return 0;
  if(currval + li[depth].val2end <= maxval)
    return 0;
  if(depth == n){
    if(currwgt <= maxwgt){
      if(currval > maxval){
        maxval = currval;
        for(i=0;i<n;i++)
          list[i].best = list[i].used;
      }
    }
    return 0;
  }
  li[depth].used = 1;
  dfs(depth+1, n, currval + li[depth].val, currwgt + li[depth].wgt, maxwgt, li);
  li[depth].used = 0;
  dfs(depth+1, n, currval, currwgt, maxwgt, li);
  return 0;
} 
