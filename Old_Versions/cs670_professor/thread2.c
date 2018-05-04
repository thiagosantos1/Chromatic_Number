
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define NT  24

int thid[NT]={13,17,23,47,13,17,23,47,13,17,23,47,13,17,23,47,13,17,23,47,13,17,23,47};

int sum = 0;

pthread_mutex_t mut;

void *worker(void *ptr);

int main(int argc, char *argv[])
{
  pthread_t th[NT];
  int i;

  pthread_mutex_init(&mut, 0);

  for(i=0;i<NT;i++)
    pthread_create(&th[i], 0, worker, & thid[i]);

  for(i=0;i<NT;i++)
    pthread_join(th[i], 0);

  printf("%d\n", sum);
}
void *worker(void *ptr)
{
  int n, tmp;

  n = * (int *) ptr;
  pthread_mutex_lock(&mut);
    tmp = sum;
    usleep(lrand48() % 10);
    tmp += n;
    sum = tmp;
  pthread_mutex_unlock(&mut);
  pthread_exit(ptr);
}

