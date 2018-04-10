
#include <findcolor.h>

pthread_mutex_t mut;

/* best number of colors found, and best coloring */

int mincolors;
int *bestcoloring;

unsigned char **a;
int *elist;
int N, nedges;

int main(int argc, char *argv[])
{
  FILE *fd;
  int i,j,k;
  pthread_t th[NT];   // data structures that pthread functions use
  int myid[NT];
  int maxd;

  if(argc < 3){
    fprintf(stderr,"usage: %s N matrix\n",argv[0]);
    exit(0);
  }
  N = atoi(argv[1]);
  fd = fopen(argv[2],"r");
  if(fd == NULL){
    fprintf(stderr,"cannot open %s\n", argv[2]);
    exit(0);
  }
  makegraph(fd);

/* create initial greedy coloring */
  maxd = maxdegree();
  mincolors = maxd + 1;
  greedycoloring(bestcoloring, mincolors);

/* starting the threads */

  pthread_mutex_init(&mut, 0);

  for(i=0;i<NT;i++)
    myid[i] = i + 2;

  for(i=0;i<NT;i++)
    pthread_create(&th[i], 0, findcoloring, &myid[i]);
  
  for(;;){
    sleep(1);
    pthread_mutex_lock(&mut);
      fprintf(stderr,"%d\n", mincolors);
    pthread_mutex_unlock(&mut);
  }

  for(i=0;i<NT;i++)
    pthread_join(th[i], 0);
}

