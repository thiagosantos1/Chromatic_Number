

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#include <pthread.h>
#include <semaphore.h>

#define NT         8
#define TRIPS      5
#define MILL 1000000

sem_t sem;
int counter = 0;

int id[]={0,1,2,3,4,5,6,7,8};

void *worker(void *parameter);

int main(int argc, char *argv[])
{
  pthread_t th[NT];
  int i;
 
  sem_init(&sem, 0, 1);
  for(i=0;i<NT;i++)
    pthread_create(&th[i], 0, worker, id+i);  // same as &id[i]
  for(i=0;i<NT;i++)
    pthread_join(th[i], 0);
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
  long t;

  me = * (int *) parameter;

  for(i=0;i<TRIPS;i++){
    t = getclock();
    sem_wait(&sem);
      fprintf(stderr," count %3d: trip %d id %d time %6ld\n", counter++, i, me, t);
      usleep((me + 1) * 100);
    sem_post(&sem);
  }
  pthread_exit(0);
}
