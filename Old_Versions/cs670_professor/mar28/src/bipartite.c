
#include <findcolor.h>
#include <pthread.h>

typedef struct thread_parameters {
  pthread_mutex_t *mutptr;
  int myid;
  GRAPH *gp;
} THREAD_PARAM;

pthread_mutex_t mut;

int idlist[NT]={0,1};

void *worker(THREAD_PARAM *p);

int bipartite(GRAPH *op)
{
  pthread_t th[NT];
  THREAD_PARAM par[NT];
  int i;

  pthread_mutex_init(&mut, 0);   // 2nd parameter is value of in the int

  for(i = 0 ; i < NT ; i++){
    par[i].mutptr = &mut;
    par[i].myid = i;
    par[i].gp = op;
    pthread_create(&th[i], 0, (void *) worker, &par[i]);
  }
  for(i = 0 ; i < NT ; i++)
    pthread_join(th[i], 0);
  return 0;
}
void *worker(THREAD_PARAM *p)
{
  GRAPH *gp;
  int *mycoloring;
  int c,n,v;

  gp = p->gp;
  n = gp->n;
  mycoloring = malloc(n*sizeof(uchar));
  c = p->myid;
  for(v=0;v<n;v++){             // not yet colored
    mycoloring[v] = c;
    c = 1 - c;
  }
  pthread_mutex_lock(p->mutptr);
/*
 * need to check if this the best coloring, etc.
 */
    for(v=0;v<n;v++)
      gp->coloring[v] = mycoloring[v];
  pthread_mutex_unlock(p->mutptr);
  free(mycoloring);
  pthread_exit(0);
}

