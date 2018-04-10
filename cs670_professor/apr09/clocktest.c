

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#include <pthread.h>
#include <semaphore.h>

#define MILL    1000000L
#define BILL 1000000000L

int counter = 0;

long getclock();

int main(int argc, char *argv[])
{
  long i, t0, t1;

  t0 = getclock();
  for(i=0;i<MILL;i++){
    t1 = getclock();
  }
  printf("%ld\n", t1 - t0);
}
long getclock()
{
  struct timeval t;
  static long t0 = 0;

  gettimeofday(&t, 0);
  if(t0 == 0){
    t0 = t.tv_sec * MILL + t.tv_usec;
    return 0;
  }
  return t.tv_sec * MILL + t.tv_usec - t0;
}
