
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define  NMAX  1000000000

#define  NT  24    // number of threads

int myid[NT];

pthread_mutex_t mut;

double sum;

void *worker(void *ptr);

int main(int argc, char *argv[])
{
  pthread_t th[NT];   // data structures that pthread functions use
  int i;

  sum = 0.0;

  pthread_mutex_init(&mut, 0);

  for(i=0;i<NT;i++)
    myid[i] = i;

  for(i=0;i<NT;i++)
    pthread_create(&th[i], 0, worker, &myid[i]);
  
  for(i=0;i<NT;i++)
    pthread_join(th[i], 0);

  printf("sum = %16.12lf\n", sum);
}
void *worker(void *ptr)
{
  double mysum;
  double fpn;
  int n;
  int id;
  int tmp;

  id = * (int *) ptr;
  mysum = 0.0;
  for(n = id+1 ; n <= NMAX ; n += NT){
    fpn = (double) n;
    mysum += 1.0/(fpn * fpn);
  }

  pthread_mutex_lock(&mut);
  sum += mysum;
  pthread_mutex_unlock(&mut);

  pthread_exit(0);
}

