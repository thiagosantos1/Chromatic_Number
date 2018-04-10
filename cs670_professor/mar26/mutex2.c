
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define NT    4

typedef struct thread_parameters {
  pthread_mutex_t *mutptr;
  int myid;
  int *doneptr;
} THREAD_PARAM;

pthread_mutex_t mut;
int done;

int idlist[NT]={0,1,2,3};

void *worker(THREAD_PARAM *p);

int main(int argc, char *argv[])
{
  pthread_t th[NT];  // list of threads
  THREAD_PARAM par[NT];
  int i, *rv;

  pthread_mutex_init(&mut, 0);   // 2nd parameter is value of in the int
  done = 0;                      // not done yet, done is false

  for(i = 0 ; i < NT ; i++){
    par[i].mutptr = &mut;
    par[i].myid = i;
    par[i].doneptr = &done;
    pthread_create(&th[i], 0, (void *) worker, &par[i]);
  }
  sleep(10);
  pthread_mutex_lock(&mut);
    done = 1;
  pthread_mutex_unlock(&mut);
  
  for(i = 0 ; i < NT ; i++){
    pthread_join(th[i], 0);
    printf("join: %d\n", i);
  }
}
void *worker(THREAD_PARAM *p)
{
  int i, mydone = 0;

  printf("thread %d reporting for duty\n", p->myid);
  for(i=1;!mydone;i++){
    sleep(1);
    printf("%3d thread %d is working\n", i, p->myid);
    pthread_mutex_lock(p->mutptr);
      mydone = *p->doneptr;
    pthread_mutex_unlock(p->mutptr);
  }
  pthread_exit(0);
}

