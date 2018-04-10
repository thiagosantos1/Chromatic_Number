
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  int i,j,k,n;
  int maxwgt,maxval;

  srand48(getpid());
  n = atoi(argv[1]);
  maxwgt = atoi(argv[2]);
  maxval = atoi(argv[3]);
  for(i=0;i<n;i++)
    printf("%d %d\n", 1 + lrand48() % maxwgt, 1 + lrand48() % maxval);
}
