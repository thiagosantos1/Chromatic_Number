
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define NT  4

int thid[NT]={13,17,23,47};

void *worker(void *ptr);

int main(int argc, char *argv[])
{
  pthread_t th[NT];
  int i;

  for(i=0;i<NT;i++)
    pthread_create(&th[i], 0, worker, & thid[i]);

  for(i=0;i<NT;i++)
    pthread_join(th[i], 0);
}
void *worker(void *ptr)
{
  int n;

  n = * (int *) ptr;
  printf("Hello from thread id %d\n", n);
  pthread_exit(ptr);
}

