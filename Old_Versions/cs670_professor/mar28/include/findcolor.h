
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#define NT             2    // number of threads

#define NOCOLOR       -1

#define GIVEUPTIME     5
#define NUMTORECOLOR   9 
#define MAXGIVEUPS   100 

#define DEBUG

#define RND(X)   (lrand48() % (X))

typedef
  unsigned char
uchar;

typedef struct userdata {
  int n;           // order of the graph
  char *filename;  // file name
} USER_PARAMS;

typedef struct graphdata {
  int n,m;        // order and size
  uchar **a;      // adjacency matrix
  int **nbr;       // list of neighbors
  int *elist;     // list of edges, two entries per edge
  int *deg;       // vertex degrees
  int *coloring;  // best coloring found
} GRAPH;

int makegraph(GRAPH *op, USER_PARAMS *ip);
int greedycoloring(GRAPH *op);
int bipartite(GRAPH *op);
int maxdegree(GRAPH *op);
void *findcoloring(void *ptr);

