
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/resource.h>

/* MASK has NC 1-bits, NC = Number of Colors */

#define MASK     ((1 << NC) - 1)

#define NMAX     256
#define DMAX      64

#define KEYDEPTH  14
#define NPROCS    24

#define MULTIPROC
#define KEEPMEPOSTED

#define DEG(X)         b[X].deg
#define COLOR(X,Y)     color[X] = Y

typedef
  unsigned char
uchar;

typedef struct vertex {
  int deg;
  int nbr[DMAX];
} VERTEX;

int N,D,NC;           // order, max degree, number colors

uchar cf[NMAX];       // colors forbidden
uchar color[NMAX];    // color used, NC means no color
int *used;         // has this color been used

uchar a[NMAX][NMAX];  // adjacency matrix (needed?)
VERTEX b[NMAX];       // adjacency list

int sig[NMAX];

int *oneleft;         // oneleft[i] >= 0 indicates the single feasible color for mask i

long calls = 0;       // dfs calls

void dfs(int v);
void vorder(int sig[]);
void setup();
void recolor(int u, int c);

int whoami;            // fake process id
FILE *logfd;           // log file descriptor

int main(int argc, char *argv[])
{
  int i,j,k;
  char filename[64];
  char fname[64];
  FILE *fd;
  int t0;

  whoami = atoi(argv[1]);
  if(whoami){
    fclose(stdin);
    fclose(stdout);
    fclose(stderr);
    if(fork())
      exit(0);
    sprintf(filename,"log.%03d",whoami);
    logfd = fopen(filename,"w");
    setbuf(logfd,0);
    setpriority(0, 0, 19);
  } else {
    logfd = stderr;
  }

  N = 216;
  fd = fopen("problem216.matrix","r");
  if(!fd){
    fprintf(stderr,"cannot open %s\n", argv[3]);
    exit(0);
  }
  NC = 3;
  used = malloc(NC*sizeof(int));
  oneleft = malloc((1 << NC) * sizeof(int));
  for(i=0;i<N;i++)
    b[i].deg = 0;
  for(i=0;i<N;i++) 
    for(j=0;j<N;j++){
      fscanf(fd,"%1d",&k);
      a[i][j] = k;
      if(k)
        b[i].nbr[b[i].deg++] = j;
    }
  fclose(fd);

  setup();
  dfs(1);
  fprintf(logfd,"%d calls\n", calls);
}
void setup()
{
  int i;

  for(i=0;i<(1 << NC);i++)
    oneleft[i] = -1;
  for(i=0;i<NC;i++)
    oneleft[MASK ^ (1 << i)] = i;
  vorder(sig);
  for(i=0;i<N;i++)
    COLOR(i,NC);
  memset(cf,0,N);    // Colors Forbidden

/* assign color 0 to vertex 0 */

  COLOR(0,0);
  for(i=0;i<DEG(0);i++)
    cf[b[0].nbr[i]] |= (1 << 0);

/* mark all but color 0 unused */

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
    m = -1;
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
      } else if(k == m && DEG(i) > DEG(v)){
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
void savestate(uchar scolor[], uchar scf[])
{
  memcpy(scf,cf,N);
  memcpy(scolor,color,N);
}
void restorestate(uchar scolor[], uchar scf[])
{
  memcpy(cf,scf,N);
  memcpy(color,scolor,N);
}
int colorvertex(int v, int c)
{
  int f,i,j,t,u;

  if(color[v] != NC){
    fprintf(logfd,"attempting to recolor %d from %d to %d\n",v,color[v],c);
    exit(0);
  }
  COLOR(v,c);                               // assign color c to v
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
    t = oneleft[cf[u]];
    if(t >= 0){
      if(!colorvertex(u,t))                   // recursively check that color assignment
        return 0;
    }
  }
  return 1;
}
void dfs(int dep)
{
  int i,u,v,c;
  uchar scolor[N];    // save copy of colors assigned
  uchar scf[N];       // save copy of Forbidden Colors
#ifdef KEEPMEPOSTED
  static int mindep = 0x7fffffff,maxdep = 0;
#endif

#ifdef MULTIPROC
  if(dep == KEYDEPTH){
    calls++;
    return;
  }
#endif

#ifdef KEEPMEPOSTED
  if(dep > maxdep){
    maxdep = dep;
    mindep = dep;
    fprintf(logfd,"%3d%15ld max %3d\n", whoami, calls, maxdep);
  } else if(dep < mindep){
    mindep = dep;
    fprintf(logfd,"%3d%15ld max %3d  mindep %3d\n", whoami, calls, maxdep, mindep);
  }
#endif

  if(dep == N){
    for(i=0;i<N;i++)
      fprintf(logfd,"%d",color[i]);
    fprintf(logfd,"\n");
    fprintf(logfd,"Success.\n");
    exit(0);
  }
  v = sig[dep];              // vertices ordered by # of lower numbered neighbors
  if(color[v] != NC){        // the color of this vertex was already forced
    dfs(dep+1);
    return;
  }
  for(c=0;c<NC;c++){
    if(color[v] != NC){
       fprintf(logfd,"error: vertex %d is not uncolored at step %d, depth %d\n",v,c,dep);
       exit(0);
    }
    if(cf[v] & (1 << c))      // c is a forbidden color
      continue;
    savestate(scolor,scf);    // save state: assigned colors and forbidden colors
    if(colorvertex(v,c)){
      used[c]++;
      dfs(dep+1);
      used[c]--;
    }
    if(used[c] == 0) return;  // if more than one color is still unused, no need to try them all
    restorestate(scolor,scf);
  }
#ifdef MULTIPROC
  if(dep == KEYDEPTH){
    fprintf(logfd,"%3d ",whoami);
    for(i=0;i<KEYDEPTH;i++)
      fprintf(logfd,"%1d",color[sig[i]]);
    fprintf(logfd," key\n");
  }
#endif
}

