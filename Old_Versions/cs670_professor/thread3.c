
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>

#define NT  24

#define LIMIT 100000000

int thid[NT];

double sum = 0;

pthread_mutex_t mut;

void *worker(void *ptr);

int main(int argc, char *argv[])
{
  pthread_t th[NT];
  int i;

  pthread_mutex_init(&mut, 0);

  for(i=0;i<NT;i++)
    thid[i] = i+1;
  for(i=0;i<NT;i++)
    pthread_create(&th[i], 0, worker, & thid[i]);

  for(i=0;i<NT;i++)
    pthread_join(th[i], 0);

  printf("%lf\n", sum);
}
void *worker(void *ptr)
{
  int i,n;
  double tmp;

  n = * (int *) ptr;
  tmp = 0;
  for(i = n; i < LIMIT ; i += NT)
    tmp += log((double) i);
  pthread_mutex_lock(&mut);
    sum += tmp;
  pthread_mutex_unlock(&mut);
  pthread_exit(ptr);
}

double add(int lo, int hi)
{
  double sum;
  int i;

  sum = 0;
  for(i = lo; i <= hi ; i++)
    sum += log((double) i);
  return sum;
}

