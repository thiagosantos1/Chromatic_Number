
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#define NT            12    // number of threads

#define NOCOLOR       -1

#define GIVEUPTIME     5
#define NUMTORECOLOR   9 
#define MAXGIVEUPS   100 

#define DEBUG

#define RND(X)   (lrand48() % (X))

#define SET_PROCS(Y)  (gc_up.procs = (Y))
#define SET_ORDER(Y)  (gc_up.n     = (Y))
#define SET_FILE(Y)   (gc_up.filename = strdup(Y))

typedef
  unsigned char
uchar;

typedef struct userdata {
  int n;           // order of the graph
  char *filename;  // file name
  int procs;
} USER_PARAMS;

typedef struct graphdata {
  int n,m;        // order and size
  uchar **a;      // adjacency matrix
  int *elist;     // list of edges, two entries per edge
  int *deg;       // vertex degrees
  int *coloring;  // best coloring found
} GRAPH;

#ifndef __XYZZY__

#define __XYZZY__

USER_PARAM gc_up;
GRAPH      gc_gr;

#endif

int makegraph(GRAPH *op, USER_PARAMS *ip);
int greedycoloring(GRAPH *op);
int bipartite(GRAPH *op);
int maxdegree(GRAPH *op);
void *findcoloring(void *ptr);

