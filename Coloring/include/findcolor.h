
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
  int order;           // order of the graph before n
  char *filename;  // file name
} USER_PARAMS;

// define a struct to be use as adjacency list
typedef struct
{
  int * nbrs; // represents which vertex are its neighbors
} ADJ_LIST;

typedef struct graphdata {
  int order; //n
  int size;    //m
  uchar **a;      // adjacency matrix
  int *elist;     // list of edges, two entries per edge
  int *deg;       // vertex degrees
  int *coloring;  // best coloring found
  int maxdegree;   // save the max degree of graph
  int is_graph_connected; // 0 to no and 1 to yes
  int minimum_order_rand; // set a minimum size of a graph, in order to try a rand search
  ADJ_LIST * adj_list; // save and adj list, to have all neighbors
} GRAPH;

int makegraph(GRAPH *op, USER_PARAMS *ip);
int greedycoloring(GRAPH *op);
int maxdegree(GRAPH *op);
void *findcoloring(void *ptr);

int bipartite(GRAPH *op);
