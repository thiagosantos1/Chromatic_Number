
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define  NT  4    // number of threads

int myid[NT];

pthread_mutex_t mut;

int sum = 0;

void *worker(void *ptr);

int main(int argc, char *argv[])
{
  pthread_t th[NT];   // data structures that pthread functions use
  int i;

  pthread_mutex_init(&mut, 0);

  for(i=0;i<NT;i++)
    myid[i] = i;

  for(i=0;i<NT;i++)
    pthread_create(&th[i], 0, worker, &myid[i]);
  
  for(i=0;i<NT;i++)
    pthread_join(th[i], 0);

  printf("sum = %d\n", sum);
}
void *worker(void *ptr)
{
  int id;
  int tmp;

  id = * (int *) ptr;
  printf("hello from id %d\n", id);

  pthread_mutex_lock(&mut);

// critical section
  tmp = sum;
  usleep(1000);
  tmp++;
  sum = tmp;

  pthread_mutex_unlock(&mut);

  pthread_exit(0);
}

