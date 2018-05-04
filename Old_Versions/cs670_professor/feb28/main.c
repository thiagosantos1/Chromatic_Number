
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define  NT  24    // number of threads

int myid[NT];

pthread_mutex_t mut;

int mincolors;
int *bestcoloring;

void *findcoloring(void *ptr);

int main(int argc, char *argv[])
{
  pthread_t th[NT];   // data structures that pthread functions use
  int i;

  N = atoi(argv[1]);
  bestcoloring = malloc(N*sizeof(int));
  sum = 0.0;

  pthread_mutex_init(&mut, 0);

  for(i=0;i<NT;i++)
    myid[i] = i;

  for(i=0;i<NT;i++)
    pthread_create(&th[i], 0, findcoloring, &myid[i]);
  
  for(i=0;i<NT;i++)
    pthread_join(th[i], 0);

}
void *worker(void *ptr)
{

  pthread_mutex_lock(&mut);
  sum += mysum;
  pthread_mutex_unlock(&mut);

  pthread_exit(0);
}

