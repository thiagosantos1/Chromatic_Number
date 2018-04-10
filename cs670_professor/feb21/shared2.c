#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/shm.h>

int main()
{
  int md;

  md = shm_open("bob", O_CREAT | O_RDWR, 0644);
  fprintf(stderr,"md=%d\n",md);
}
