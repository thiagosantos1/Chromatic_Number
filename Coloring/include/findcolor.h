
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#define NT            24    // number of threads
#define NOCOLOR       -1

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
  int give_up_time, num_to_recolor, max_give_ups;  
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
  int * available_colors; // keep all remaining colors for each vertex(one bit for each color)
  int maxdegree;   // save the max degree of graph
  int vertex_max_degre; // save which vertex has the highest degree
  int is_graph_connected; // 0 to no and 1 to yes
  int mincolors;   // min colors userd so far/chromatic number
  int chromatic;   // save the answer for the chromatic number
  ADJ_LIST * adj_list; // save and adj list, to have all neighbors
} GRAPH;

int makegraph(GRAPH *op, USER_PARAMS *ip);
int greedycoloring(GRAPH *op);
int maxdegree(GRAPH *op);
void rand_search(GRAPH *op,USER_PARAMS *ip);
void exh_search(GRAPH *op,USER_PARAMS *ip);
int bipartite(GRAPH *op);
