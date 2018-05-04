
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NMAX        1024

typedef
  unsigned char
uchar;

int N, M, NC;

uchar a[NMAX][NMAX];

int main(int argc, char *argv[])
{
  int c,i,j,k,u,v;
  int nclause;
  char filename[64];
  FILE *fd;

  N  = atoi(argv[1]);
  NC = atoi(argv[2]);
  fd = fopen(argv[3],"r");
  M  = 0;
  for(i=0;i<N;i++)
    for(j=0;j<N;j++){
      fscanf(fd,"%1d", &k);
      a[i][j] = k;
      if(k && i < j) M++;
    }
  fclose(fd);

  for(i=0;i<N-1;i++)
    for(j=i+1;j<N;j++)
      if(a[i][j] != a[j][i]){
        fprintf(stderr,"inconsistency at %d-%d\n",i,j);
        exit(0);
      }
  printf("p cnf %d %d\n", NC*N, N+M*NC);
  k = 0;
  for(i=0;i<N;i++){
    for(j=0;j<NC;j++)
      printf("%4d", ++k);
    printf("%4d\n", 0);
  }
  for(i=0;i<N-1;i++)
    for(j=i+1;j<N;j++)
      if(a[i][j]){
        for(c=0;c<NC;c++)
          printf("%4d %4d  0\n", -(i*NC + c + 1),  -(j*NC + c + 1));
      }
}
