
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#include "lightswitch.h"

LIGHTSWITCH *init_lightswitch()
{
  LIGHTSWITCH *ptr;

  ptr = malloc(sizeof(LIGHTSWITCH));
  ptr->counter = 0;
  sem_init(&ptr->mut,0,1);
  return ptr;
}
void lock(LIGHTSWITCH *ptr, sem_t *semptr)
{
  sem_wait(&ptr->mut);
  ptr->counter++;
  if(ptr->counter == 1)
    sem_wait(semptr);
  sem_post(&ptr->mut);
}
void unlock(LIGHTSWITCH *ptr, sem_t *semptr)
{
  sem_wait(&ptr->mut);
  ptr->counter--;
  if(ptr->counter == 0)
    sem_post(semptr);
  sem_post(&ptr->mut);
}

