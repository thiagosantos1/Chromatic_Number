
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

#define Color_1 	1
#define Color_2		2


typedef
  unsigned char
uchar;

typedef struct userdata {
  int n;           // order of the graph
  char *filename;  // file name
} USER_PARAMS;

// define a struct to be use as adjacency list
typedef struct
{
  int * nbrs; // represents which vertex are its neighbors
} ADJ_LIST;

typedef struct graphdata {
  int n,m;        // order and size
  uchar **a;      // adjacency matrix
  int *elist;     // list of edges, two entries per edge
  int *deg;       // vertex degrees
  int *coloring;  // best coloring found
  ADJ_LIST * adj_list; // save and adj list, to have all neighbors
} GRAPH;

int makegraph(GRAPH *op, USER_PARAMS *ip);
int greedycoloring(GRAPH *op);
int maxdegree(GRAPH *op);
void *findcoloring(void *ptr);

int bipartite(GRAPH *op);
