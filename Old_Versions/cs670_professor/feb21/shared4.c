#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/shm.h>

#define K  1024

int main()
{
  int md;
  int n;
  char b[K];

  md = shm_open("bob", O_RDONLY, 0644);
  n = read(md,b,K);
  b[n] = 0;
  printf("read: %s", b);
}
