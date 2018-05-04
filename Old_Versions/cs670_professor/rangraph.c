
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define RND(X) (random()%(X))
#define DEG(X) b[X].deg

#define MP 25000

typedef
  unsigned char
uchar;

uchar **a;

int P,Q;

int main(int argc, char *argv[])
{
  int h,i,j,k,u,v;

  srandom(getpid());
  if(argc < 3){
    fprintf(stderr,"usage: %s NumberVertices EdgeProbability (out of 100)\n",argv[0]);
    exit(0);
  }
  P = atoi(argv[1]);
  Q = atoi(argv[2]);
  a = (uchar **) malloc(P*sizeof(uchar *));
  for(i=0;i<P;i++)
    a[i] = (uchar *) malloc(P*sizeof(uchar));
  for(i=0;i<P;i++){
    a[i][i] = 0;
    for(j=i+1;j<P;j++)
      a[i][j] = a[j][i]= (RND(100) < Q) ? 1 : 0;
  }
  for(i=0;i<P;i++){
    for(j=0;j<P;j++)
      printf("%1d",a[i][j]);
    printf("\n");
  }
}
