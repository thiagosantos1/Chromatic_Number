#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define K          1000
#define MILLION 1000000

int adder(int a[MILLION], int start, int finish);

int main()
{
  int a[MILLION];
  int i,j,k,n,mysum,total;
  int *sumptr;
  int id;
  int status;

  srand48(getpid());
  for(n=0;n<MILLION;n++)
    a[n] = lrand48() % K;

  id = shmget(IPC_PRIVATE, sizeof(int), 0660);
  sumptr = shmat(id,0,0);

  fprintf(stderr,"%d numbers\n", n);

  *sumptr = 0;
  if(fork() == 0){             /* child */
    mysum = adder(a,0,n/2-1);
    *sumptr = mysum;
    exit(0);
  } else {                        /* parent */
    mysum = adder(a,n/2,n-1);
    wait(&status);
    fprintf(stderr,"status=%d\n", status);
    *sumptr += mysum;
    printf("%d\n", *sumptr);
  }
}
int  adder(int a[MILLION], int start, int finish)
{
  int i,sum;

  fprintf(stderr,"pid %d is adding from %d to %d\n", getpid(), start, finish);
  sum = 0;
  for(i=start ; i <= finish ; i++)
    sum += a[i];
  return sum;
}
