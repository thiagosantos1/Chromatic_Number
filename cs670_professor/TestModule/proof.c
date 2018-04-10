
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* MASK has NC 1-bits, NC = Number of Colors */

#define MASK     ((1 << NC) - 1)

#define NMAX     512
#define DMAX      16

#define KEYDEPTH  10
#define NPROCS   225

#define DEG(X)         b[X].deg
#define RECOLOR(X,Y)   color[X] = Y

typedef
  unsigned char
uchar;

typedef struct vertex {
  int deg;
  int nbr[DMAX];
} VERTEX;

int N,D,NC;

uchar *cf;
int *used;
int *oneleft;
int *sig;

uchar **a;
VERTEX *b;       // adjacency list

long calls = 0;        // dfs calls

void vorder(int sig[]);
void setup(uchar color[]);
void deallocate(void);
void addedge(int u, int v);
int allocate(int n, int nc);
int dfs(int dep, uchar color[]);

int allocate(int n, int nc)
{
  int i;

  N = n;
  D = n-1;
  NC = nc;
  b = malloc(N*sizeof(VERTEX));
  for(i = 0 ; i < N ; i++)
    b[i].deg = 0;
  a = malloc(N*sizeof(uchar *));
  for(i = 0 ; i < N ; i++){
    a[i] = malloc(N*sizeof(uchar));
    memset(a[i], 0, N*sizeof(uchar));
  }
  cf = malloc(N*sizeof(uchar));
  used = malloc(NC*sizeof(int));
  oneleft = malloc((1 << NC)*sizeof(int));
  sig = malloc(N*sizeof(int));

  return 1;   // for future use and taking into account malloc failures
}
void deallocate()
{
  int i;

  free(b);
  for(i = 0 ; i < N ; i++)
    free(a[i]);
  free(a);
  free(cf);
  free(used);
  free(oneleft);
  free(sig);
}
void addedge(int u, int v)
{
  a[u][v] = 1;
  b[u].nbr[b[u].deg++] = v;
  a[v][u] = 1;
  b[v].nbr[b[v].deg++] = u;
}
void setup(uchar color[])
{
  int i;

  for(i=0;i<(1 << NC);i++)
    oneleft[i] = -1;
  for(i=0;i<NC;i++)
    oneleft[MASK ^ (1 << i)] = i;

  vorder(sig);

  RECOLOR(0,0);
  for(i=1;i<N;i++)
    RECOLOR(i,NC);

  memset(cf,0,N);
  for(i=0;i<DEG(0);i++)
    cf[b[0].nbr[i]] |= (1 << 0);

  for(i=0;i<NC;i++)
    used[i] = 0;
  used[0] = 1;
}
void vorder(int sig[])
{
  uchar f[N];
  int i,j,k,m,t,v;

  memset(f,0,N);
  sig[0] = 0;
  f[0] = 1;
  for(t=1;t<N;t++){
    m = v = -1;
    for(i=1;i<N;i++){
      if(f[i])
        continue;
      k = 0;
      for(j=0;j<t;j++)
        if(a[i][sig[j]])
          k++;
      if(k > m){
        m = k;
        v = i;
      }
    }
    sig[t] = v;
    f[v] = 1;
  }
#ifdef DEBUG
  for(i=0;i<N;i++)
    printf("%3d%6d\n",i,sig[i]);
#endif
}
int colorvertex(int v, int c, uchar color[])
{
  int i,t,u;

  if(color[v] != NC){
    fprintf(stderr,"attempting to recolor %d from %d to %d\n",v,color[v],c);
    exit(0);
  }
  RECOLOR(v,c);                               // assign color c to v
  for(i=0;i<DEG(v);i++){                   
    u = b[v].nbr[i];                          // for each neighbor of v
    if(color[u] == c){                        // if it's color c, give up
      return 0;
    } else if(color[u] < NC){                 // if it's already colored, fine
      continue;
    }
    if(cf[u] & (1 << c))                      // if color c already forbidden for u, fine
      continue;
    cf[u] |= (1 << c);                        // forbid c for u
    if((color[u] == NC) && (cf[u] == MASK))   // if no colors are left, give up
      return 0;
    t = oneleft[cf[u]];                       // if only one color left, color it
    if(t >= 0){
      if(!colorvertex(u,t,color))             // recursively check that color assignment
        return 0;
    }
  }
  return 1;
}
int dfs(int dep, uchar color[])
{
  int i,v,c,rv;
  uchar scolor[N];
  uchar scf[N];
#ifdef KEEPMEPOSTED
  static int mindep = 0x7fffffff,maxdep = 0;
#endif

#ifdef KEEPMEPOSTED
  if(dep > maxdep){
    maxdep = dep;
    mindep = dep;
    fprintf(stderr,"%3d%15ld max %3d\n", whoami, calls, maxdep);
  } else if(dep < mindep){
    mindep = dep;
    fprintf(stderr,"%3d%15ld max %3d  mindep %3d\n", whoami, calls, maxdep, mindep);
  }
#endif

  if(dep == N){
    fprintf(stderr,"Success.\n");
    for(i=0;i<N;i++)
      fprintf(stderr,"%d",color[i]);
    fprintf(stderr,"\n");
    return 1;
  }
  v = sig[dep];              // vertices ordered by # of lower numbered neighbors
  if(color[v] != NC){        // the color of this vertex was already forced
    return dfs(dep+1,color);
  }
  for(c=0;c<NC;c++){
    if(color[v] != NC){
       fprintf(stderr,"error: vertex %d is not uncolored at step %d, depth %d\n",v,c,dep);
       return -1;
    }
    if(cf[v] & (1 << c))      // c is a forbidden color
      continue;
  
    memcpy(scf,cf,N);
    memcpy(scolor,color,N);

    if(colorvertex(v,c,color)){
      used[c]++;
      rv = dfs(dep+1, color);
      if(rv) return rv;
      used[c]--;
    }
    if(used[c] == 0) return 0;  // if more than one color is still unused, no need to try them all

    memcpy(cf,scf,N);
    memcpy(color,scolor,N);
  }
  return 0;
}

