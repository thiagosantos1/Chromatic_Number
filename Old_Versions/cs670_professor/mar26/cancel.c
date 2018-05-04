
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define NT    4

int idlist[NT]={0,1,2,3};

void *worker(int *idptr);

int main(int argc, char *argv[])
{
  pthread_t th[NT];  // list of threads
  int i, *rv;

  for(i = 0 ; i < NT ; i++)
    pthread_create(&th[i], 0, (void *) worker, &idlist[i]);

  for(i = 0 ; i < NT ; i++){
    sleep(5);
    pthread_cancel(th[i]);
  }
  for(i = 0 ; i < NT ; i++){
    pthread_join(th[i], 0);
    printf("join: %d\n", i);
  }
}
void *worker(int *idptr)
{
  int myid;
  int i;
  int oldstate;

  myid = *idptr;
  printf("thread %d reporting for duty\n", myid);
  if(myid == 1)
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &oldstate);
  for(i=1;;i++){
    sleep(1);
    printf("%3d thread %d is working\n", i, myid);
    if(myid == 1 && i == 20)
      pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &oldstate);
  }
  pthread_exit(idptr);
}
