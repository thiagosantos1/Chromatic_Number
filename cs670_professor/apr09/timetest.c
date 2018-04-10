

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#include <pthread.h>
#include <semaphore.h>

#define NT           8
#define TRIPS  1000000
#define MILL   1000000

sem_t sem;
long global = 0;

int id[]={0,1,2,3,4,5,6,7,8};

void *worker(void *parameter);
long getclock();

int main(int argc, char *argv[])
{
  pthread_t th[NT];
  int i;
  long t0,t1;

  sem_init(&sem, 0, 1);
  t0 = getclock();
  for(i=0;i<NT;i++)
    pthread_create(&th[i], 0, worker, id+i);  // same as &id[i]
  for(i=0;i<NT;i++)
    pthread_join(th[i], 0);
  printf("%ld %ld\n", getclock() - t0, global);
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
void *worker(void *parameter)
{
  int i, me;

  me = * (int *) parameter;

  for(i=0;i<TRIPS;i++){
    sem_wait(&sem);
      global++;
    sem_post(&sem);
  }
  pthread_exit(0);
}
