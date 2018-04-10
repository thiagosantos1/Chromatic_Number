
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NT         2

pthread_mutex_t *mp;

void *thA(void *nothing);
void *thB(void *nothing);

sem_t s,t;

int main()
{
  pthread_t th[NT];
  int i;

  sem_init(&s, 0, -1);
  sem_init(&t, 0, -1);

  pthread_create(&th[0], 0, (void *) thA, 0);
  pthread_create(&th[1], 0, (void *) thB, 0);

  for(i=0;i<NT;i++)
    pthread_join(th[i], 0);
  fputc('\n',stderr);
}
void *thA(void *nothing)
{
  int i;
  char *p="NIN TT NVRIY";

  for(i=0;p[i];i++){
    sem_wait(&s);
    fputc(p[i],stderr);
    sem_post(&t);
  }
  pthread_exit(0);
}
void *thB(void *nothing)
{
  int i;
  char *p="IDAASAEUIEST";

  for(i=0;p[i];i++){
    fputc(p[i],stderr);
    sem_post(&s);
    sem_wait(&t);
  }
  pthread_exit(0);
}
