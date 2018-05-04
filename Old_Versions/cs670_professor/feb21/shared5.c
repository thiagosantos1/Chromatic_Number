#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/shm.h>

int main()
{
  int md;
  sem_t s, *semptr;

  md = shm_open("mysemaphore", O_CREAT | O_RDWR, 0644);
  semptr = shmat(md, &s, 0);
  fprintf(stderr,"md=%d\n",md);
}
