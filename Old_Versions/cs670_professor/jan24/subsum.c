
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define USERANDOM

#define SUCCESSMASK  (0x700)

#define K           1024

#define N             30    // number of numbers
#define M     1000000000L   // max value for a number
#define TAR  10000000000L   // the sum I want

#define SPLITDEPTH    10    // work begins to be divided among process at this level
#define NPROCS         4    // number of processes

#define PROBFILE    "numbers.txt"   // the list of numbers

typedef
  unsigned char
uchar;

long calls = 0;
long list[N];               // the numbers

void runproc(int id);
void dfs(int id, int depth, long sum, uchar st[]);

int main(int argc, char *argv[])
{
  int i,k;
  int status,winner;
  FILE *fd;
  int pidlist[NPROCS];

  srand48(getpid());

#ifdef USERANDOM
  for(i=0;i<N;i++)
    list[i] = lrand48() % M;
#else
  fd = fopen(PROBFILE,"w");
  for(i=0;i<N;i++)
    fprintf(fd,"%ld\n", list[i]);
  fclose(fd);
#endif

  for(i=0;i<NPROCS;i++)
    if((pidlist[i] = fork()) == 0)
      runproc(i);
  for(k=0;k<NPROCS;k++){
    wait(&status);
    fprintf(stderr,"status value: %04x\n", status);
    if(status & SUCCESSMASK){
      winner = (status >> 8) - 1;
      for(i=0;i<NPROCS;i++)
        if(i != winner)
          kill(pidlist[i], 9);
      exit(0);
    }
  }
  fprintf(stderr,"no solutions\n");
}
void runproc(int id)
{
  int i;
  uchar used[N];
  char outfile[K];

  sprintf(outfile,"out.%02d", id);
  fclose(stderr);
  fclose(stdout);
  stdout = stderr = fopen(outfile,"w");

  memset(used,0,N);
  dfs(id,0,0,used);
  fprintf(stderr,"id %d: no solutions\n");
  exit((id+1) << 4);   // failure
}
void dfs(int id, int depth, long sum, uchar used[])
{
  int i;

  if(depth == SPLITDEPTH){
    calls++;
    if((calls % NPROCS) != id)
      return;
  }
  if(sum == TAR){
    fprintf(stderr,"id %2d found a solution:", id);
    for(i=0;i<depth;i++)
      fprintf(stderr,"%1d",used[i]);
    fprintf(stderr,"\n");
    exit(id+1);          // success
  }
  if(depth == N)
    return;
  if(sum + list[depth] <= TAR){
    used[depth] = 1;
    dfs(id,depth+1,sum+list[depth],used);
    used[depth] = 0;
  }
  dfs(id,depth+1,sum,used);
}
