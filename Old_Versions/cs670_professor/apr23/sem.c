
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <semaphore.h>

#define NTH    24   // number of thread variables
#define NID  4096   // number of thread ids

/*
#define WORK      usleep(lrand48() & 0xfff)
#define FIDDLE    usleep(lrand48() & 0x0ff)
*/

#define WORK      usleep(0)
#define FIDDLE    usleep(0)

typedef
  unsigned char
uchar;

/*
 * for the starvation-free mutex
 */
 
int room1, room2;
sem_t mutex, t1, t2;

/*
 * for telling the main thread who wants to leave
 */

sem_t finish, waitready;   // can we replace these 2 mutexs by 1 ?
int waitingid = -1;

int badcount = 0;
int exitcount;

void *thA(void *nothing);
int findFreeThread(uchar u[]);
void changeWaitingId(int id);

int main()
{
  int copyid, *exitid;
  uchar flag;
  int id[NID];
  pthread_t th[NTH];

  uchar inuse[NTH];

  int thr2id[NTH];  // tells us which id a thread is running
  int id2thr[NID];  // tells us which thread n id is using
  int i,j,k,ndone;

  srand48(getpid());

  for(i=0;i<NID;i++)  // setup the list of ids
    id[i] = i;

  for(i=0;i<NID;i++)  // setup id2thr: no id has a thread yet
    id2thr[i] = -1;
  for(i=0;i<NTH;i++)  // no thread is in use
    inuse[i] = 0;
  for(i=0;i<NTH;i++)  // no thread is running an id
    thr2id[i] = -1;
  srandom(getpid());

  exitcount = 0;
/*
 * setup the starvation free mutex
 */
  room1 = room2 = 0;
  sem_init(&mutex,  0, 1);
  sem_init(&t1,     0, 1);
  sem_init(&t2,     0, 0);

  sem_init(&finish, 0, 1);
  sem_init(&waitready, 0, 1);

  i = 0;
  ndone = 0;
  while(ndone < NID){
    if(i < NID){
      k = findFreeThread(inuse);
      if(k >= 0){
        inuse[k] = 1;
        fprintf(stderr,"starting id %d using thread %d\n", i, k);
        pthread_create(&th[k], 0, (void *) thA, (void *)(&id[i]));
        id2thr[i] = k;
        thr2id[k] = i;
        i++;
      }
    }
    FIDDLE;
    flag = 0;
    sem_wait(&finish);
      if(waitingid >= 0){
        fprintf(stderr,"joining id %d using thread %d\n", waitingid, id2thr[waitingid]);
        k = id2thr[waitingid];
        pthread_join(th[k],0);
        inuse[k] = 0;
        changeWaitingId(-1);
        id2thr[i] = -1;
        thr2id[k] = -1;
        ndone++;
        flag = 1;
      }
    sem_post(&finish);
    if(flag)
      sem_post(&waitready);
  }
  printf("badcount = %d\n", badcount);
}
void *thA(void *nothing)
{
  int id, done;

  id = * (int *) nothing;
  
/* BEGIN OF starvation free mutex */

  sem_wait(&mutex);
    room1++;
  sem_post(&mutex);

  sem_wait(&t1);
    room2++;
    sem_wait(&mutex);
      room1--;
    if(room1 == 0){
      sem_post(&mutex);
      sem_post(&t2);
    } else {
      sem_post(&mutex);
      sem_post(&t1);
    }

  sem_wait(&t2);
    room2--;
/*
 * critical section
 */
    WORK;
/*
 * end of critical section
 */
    if(room2 == 0)
      sem_post(&t1);
    else
      sem_post(&t2);

/* END OF starvation free mutex */

  fprintf(stderr,"thread %d wants to exit\n", id);
  for(;;){
    sem_wait(&waitready);
    sem_wait(&finish);
      if(waitingid >= 0){
        done = 0;
        badcount++;
      } else {
        done = 1;
        changeWaitingId(id);
      }
    sem_post(&finish);
    if(done)
      break;
    FIDDLE;
  }
  fprintf(stderr,"thread %d exiting\n", id);
  pthread_exit(0);
}
int findFreeThread(uchar u[])
{
  int i;

  for(i=0;i<NTH;i++)
    if(!u[i])
      return i;
  return -1;
}
void changeWaitingId(int id)
{
  waitingid = id;
}
