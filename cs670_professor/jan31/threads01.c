
#include <stdio.h>
#include <pthread.h>

#define  NT  4    // number of threads

int myid[NT];

void *worker(void *ptr);

int main(int argc, char *argv[])
{
  pthread_t th[NT];   // data structures that pthread functions use
  int i;

  for(i=0;i<NT;i++)
    myid[i] = i;

  for(i=0;i<NT;i++)
    pthread_create(&th[i], 0, worker, &myid[i]);
  
  for(i=0;i<NT;i++)
    pthread_join(th[i], 0);
}
void *worker(void *ptr)
{
  int id;

  id = * (int *) ptr;

  printf("hello from id %d\n", id);
  pthread_exit(0);
}

