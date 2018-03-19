// File disigned to check if a graph is bipartite or not
// Also, to check if graph is connected or not

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h> 

#define CHUNK  		1
#define X		255 // Max size of a line in a file
#define NO_COLOR 	-1
// used to assigned one color to each neighbor. If at any time cannot color, it means it's not bipartite
#define Color_1 	1
#define Color_2		2

// define a struct to be use as adjacency list
typedef struct
{
  int degre; // to now how many neighors this vertex has / size of the linked list
  int size;   // how many itens allocated
  int * nbrs; // represents which vertex are its neighbors
  int color; // save how many colors is available for that vertex
} ADJ_LIST;


ADJ_LIST * adj_list;
short N;        // number of vertexes // dinymic allocated, based on the name of the program

void init_vertex(int num_vert); // initialize N, that represents how many vertex in the graph
void init_adjList(void); // initialize the adj list array
void update_alist(int u, int v);
void display_graph(void);
int get_vertex_not_colored(void); // return a vertex that did not get colored after dfs
int bad_neighbors(int vertex); // return 1 if any neighbor of vertex got the same color as him
//color vertex with color 1 or 2, oposite of the previous call(parent). Then checks if any
//					  neighbor got same color. If so, return false 
int dfs_bipartite_check(int vertex, int color); 

void init_vertex(int num_vert)
{
  N = num_vert;
}

void init_adjList()
{
  adj_list = malloc(N* sizeof(ADJ_LIST));
  
  for(int i=0;i<N;i++){
    adj_list[i].degre  = 0;
    adj_list[i].size = 0;
    adj_list[i].nbrs = 0;  // null pointer
    adj_list[i].color = NO_COLOR; 
  }
  
}

void update_alist(int u, int v)
{
  int tmp;
  
  if(adj_list[u].degre >= adj_list[u].size){
    if(adj_list[u].size == 0){
      adj_list[u].size = CHUNK;
      adj_list[u].nbrs = malloc(CHUNK * sizeof(int));
    }else{
      adj_list[u].size += CHUNK;
      tmp = adj_list[u].size;
      adj_list[u].nbrs = realloc(adj_list[u].nbrs, tmp * sizeof(int));
    }
  }
  adj_list[u].nbrs[adj_list[u].degre++] = v;
}

void display_graph()
{
  
  for(int i=0; i<N; i++){
    printf("Vertex %d Color %d\nNeighbors: ",i, adj_list[i].color );
    for(int j=0; j<adj_list[i].size; j++){
      printf("Nbr %d Color %d ", adj_list[i].nbrs[j], adj_list[adj_list[i].nbrs[j]].color);
    }
    printf("\n\n");
  }
}

int dfs_bipartite_check(int vertex, int color)
{
  int vert_ngbr, flag=1,i;
  
  adj_list[vertex].color = color;
  color = color==Color_1 ? Color_2:Color_1;
  for(i=0; i<adj_list[vertex].size; i++){
    vert_ngbr = adj_list[vertex].nbrs[i];
    if(adj_list[vert_ngbr].color == NO_COLOR){
      flag = dfs_bipartite_check(vert_ngbr,color);
      if(flag<=0)
	break;
    } else if(adj_list[vert_ngbr].color == adj_list[vertex].color){
    
      return 0;
    }
  }
  
  return flag;
}

int bad_neighbors(int vertex)
{
  for(int i=0; i< adj_list[vertex].size; i++){
    if(adj_list[vertex].color == adj_list[adj_list[vertex].nbrs[i]].color )
      return 1;
  }
  
  return -1; // there is not bad neighbrs
}

int get_vertex_not_colored()
{
  for(int i=0; i< N; i++){
    if(adj_list[i].color == NO_COLOR)
      return i;
  }
  
  return -1;
  
}

