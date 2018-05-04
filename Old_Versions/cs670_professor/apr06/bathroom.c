
/*
  - Unisex bathroom problem from the Little Book of Semaphores
  - Uses lightswitch from lightswitch.c.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#include "lightswitch.h"

#define K        1024
#define NT         50
#define CAPACITY    3

typedef struct user {
  char *name;
  int sex;
  int arr,dur;   // arrival and duration
} USER;

sem_t empty;
sem_t multigirl,multiboy;

LIGHTSWITCH *girlswitch, *boyswitch;

void *thread_girl(void *ptr);
void *thread_boy(void *ptr);

int main(int argc, char *argv[])
{
  int i,n;
  int arr,dur;
  char name[K];
  char sex;
  pthread_t th[NT];
  USER *p;
  FILE *fd;

  fd = fopen(argv[1],"r");
  if(!fd){
    perror("fopen");
    exit(0);
  }
  sem_init(&empty, 0, 1);
  sem_init(&multiboy , 0, CAPACITY);
  sem_init(&multigirl, 0, CAPACITY);

  boyswitch  = init_lightswitch();
  girlswitch = init_lightswitch();
  n = 0;
  while(fscanf(fd,"%s %c %d %d\n",name,&sex,&arr,&dur) == 4){
    p = malloc(sizeof(USER));
    p->name = strdup(name);
    p->sex = (sex == 'F') ? GIRL : BOY;
    p->arr = arr;
    p->dur = dur;
    if(p->sex == GIRL)
      pthread_create(&th[n++], 0, (void *) thread_girl, p);
    else
      pthread_create(&th[n++], 0, (void *) thread_boy , p);
  }
  for(i=0;i<n;i++)
    pthread_join(th[i], 0);
}
void *thread_girl(void *ptr)
{
  USER *p;

  p = (USER *) ptr;
  lock(girlswitch,&empty);
  sem_wait(&multigirl);
  printf("%s in the bathroom\n",p->name);
  sleep(p->dur);
  sem_post(&multigirl);
  unlock(girlswitch,&empty);
  printf("%s leaves bathroom\n",p->name);

  free(p);
  pthread_exit(0);
}
void *thread_boy(void *ptr)
{
  USER *p;

  p = (USER *) ptr;
  lock(boyswitch,&empty);
  sem_wait(&multiboy);
  printf("%s in the bathroom\n",p->name);
  sleep(p->dur);
  sem_post(&multiboy);
  unlock(boyswitch,&empty);
  printf("%s leaves bathroom\n",p->name);

  free(p);
  pthread_exit(0);
}
