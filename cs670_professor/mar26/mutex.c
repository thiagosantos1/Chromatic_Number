
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define NT    4

pthread_mutex_t mut;
int done;

int idlist[NT]={0,1,2,3};

void *worker(int *idptr);

int main(int argc, char *argv[])
{
  pthread_t th[NT];  // list of threads
  int i, *rv;

  pthread_mutex_init(&mut, 0);   // 2nd parameter is value of in the int
  done = 0;                      // not done yet, done is false

  for(i = 0 ; i < NT ; i++)
    pthread_create(&th[i], 0, (void *) worker, &idlist[i]);

  sleep(10);
  pthread_mutex_lock(&mut);
    done = 1;
  pthread_mutex_unlock(&mut);
  
  for(i = 0 ; i < NT ; i++){
    pthread_join(th[i], 0);
    printf("join: %d\n", i);
  }
}
void *worker(int *idptr)
{
  int myid;
  int i;
  int mydone = 0;

  myid = *idptr;
  printf("thread %d reporting for duty\n", myid);
  for(i=1;!mydone;i++){
    sleep(1);
    printf("%3d thread %d is working\n", i, myid);
    pthread_mutex_lock(&mut);
      mydone = done;
    pthread_mutex_unlock(&mut);
  }
  pthread_exit(idptr);
}
