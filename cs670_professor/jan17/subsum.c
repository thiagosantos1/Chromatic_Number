
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MULTIPROC
#define KEYDEPTH      13
#define NPROCS        24

#define K           1024

#define N             30    // size of set
#define MAX  1000000000L    // max value in set
#define TAR 10000000000L  // target

typedef
  unsigned char
uchar;

long calls = 0;

int id;

void dfs(int depth, long sum, uchar used[], long li[]);

int main(int argc, char *argv[])
{
  long list[N];
  uchar used[N];
  char filename[K];
  int i;

#ifdef MULTIPROC
  id = atoi(argv[1]);
  sprintf(filename,"log.%02d", id);
  fclose(stdout);
  fclose(stderr);
  stderr = stdout = fopen(filename,"w");
#endif

  srand48(2);
  for(i=0;i<N;i++)
    list[i] = 1 + lrand48() % MAX;

  memset(used, 0, N*sizeof(uchar));

  dfs(0, 0L, used, list);
  fprintf(stderr,"no solutions\n");
}
void dfs(int depth, long sum, uchar used[], long li[])
{
  int i;

#ifdef MULTIPROC
  if(depth == KEYDEPTH){
    calls++;
    if(calls % NPROCS != id)
      return;
  }
#endif

  if(sum == TAR){
    for(i=0;i<N;i++)
      if(used[i])
        printf("%7ld\n", li[i]);
    exit(0);
  } else if(depth >= N){
    return;
  }
  if(li[depth] + sum <= TAR){
    used[depth] = 1;
    dfs(depth+1, sum+li[depth], used, li);
    used[depth] = 0;
  }
  dfs(depth+1, sum, used, li);
}
