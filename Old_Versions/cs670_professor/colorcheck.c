
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef
  unsigned char
uchar;

unsigned char **a;

int N;

int main(int argc, char *argv[])
{
  FILE *fd;
  int i,j,k;
  int *color;

  if(argc < 3){
    fprintf(stderr,"usage: %s N matrix\n",argv[0]);
    exit(0);
  }
  N = atoi(argv[1]);
  fd = fopen(argv[2],"r");
  if(fd == NULL){
    fprintf(stderr,"cannot open %s\n", argv[1]);
    exit(0);
  }
  a = malloc(N*sizeof(uchar *));
  for(i=0;i<N;i++)
    a[i] = malloc(N*sizeof(uchar));
  for(i=0;i<N;i++)
    for(j=0;j<N;j++){
      fscanf(fd,"%1d",&k);
      a[i][j] = k;
    }
  fclose(fd);
  color = malloc(N*sizeof(int));
  for(i=0;i<N;i++)
    scanf("%d",&color[i]);
  for(i=0;i<N-1;i++)
    for(j=i+1;j<N;j++)
      if(a[i][j] && color[i] == color[j]){
        fprintf(stderr,"Bad coloring: adjacent vertices %d and %d both have color %d\n",i,j,color[i]);
        exit(0);
      }
}
