#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/shm.h>

#define MESS "Welcome to shared memory.\n"

int main()
{
  int md;

  md = shm_open("bob", O_RDWR, 0644);
  write(md, MESS, strlen(MESS));
}
