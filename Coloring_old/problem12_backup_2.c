#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>


#define COLORS		 4 // size of the adjacency Matrix
#define X		 255 // Max size of a line in a file
#define NO_COLOR	-1
#define CHUNK  		16
#define COLUMNS   2


// define a struct to be use as adjacency list
typedef struct
{
  int degre; // to now how many neighors this vertex has / size of the linked list
  int size;   // how many itens allocated
  int * nbrs; // represents which vertex are its neighbors
} ADJ_LIST;


int * *adj_mtx; // 0-1 if both nodes has an edge // gonna alocate 
int *color; // has size of N, and each position represents each class. Then, each position gets a color(0,1,2...Colors)
int * *color_arc; // matrix 2xN that has the color assigned and the colors remainings for each node
ADJ_LIST * adj_list;
int N;        // number of vertexes // dinymic allocated, based on the name of the program

void init_vertex(char * filename); // initialize N, that represents how many vertex in the graph
void init_adjList(); // initialize the adj list array
void init_colors();
void init_matrix();

// function to initialize the color_arc matrix, that works with forward checking CSP constraint
void init_color_arc();
void print_matrix();
// function based only on the adjancency matrix to determine if it's safe to color the vertex v with color c
int isSafe_matrix (int v,  int c);
// function based only on the adjancency list to determine if it's safe to color the vertex v with color c - faster 
int isSafe_adjList(int v,  int c);
int dfs_coloring(int v);
int coloring_CSP_constraint(int v, int deph);
void printSolution();

int how_many_bits_sets(int num); // return how many bits are set in a number // how many colors available
int highest_degree(); 
int pick_next_vertex(); // pick the vertex in the graph that has the minimum num of available colors 

int isColorAvailable(int v, int c); // check if color c is available(if bit is set at that c position)
void update_alist(int u, int v);

int main(int argc, char * argv[])
{
  if(argc<2){
    printf("File name <%s usage>\n", argv[0]);
    return 0;
  }
  if(COLORS <1){
    printf("No solutions for %d colors\n", COLORS);
    return 0;
  }
  
  init_vertex(argv[1]); // initialize how many vertex there are in the graph, based on the name of the file
  init_colors();
  init_matrix();
  init_adjList();
  init_color_arc();
  
  char * filename = argv[1], *token;
  FILE * fp = fopen(filename, "r");
  char class_1[X], class_2[X];
  int num_class1=0, num_class2=0;
  while( fscanf(fp,"%s %s", class_1, class_2) == 2){
    // class 1
    token = strtok(class_1, "cid");
    num_class1 = atoi(token);
    
    // class 2
    token = strtok(class_2, "cid");
    num_class2 = atoi(token);
    // add arc 
    adj_mtx[num_class1][num_class2] = 1;
    adj_mtx[num_class2][num_class1] = 1;
    
    update_alist(num_class1,num_class2);
    update_alist(num_class2,num_class1);
    
  }
  // save the vertex with more degrees, to start the search
  int vertex_hightest_deg = highest_degree();

  // Call dfs_coloring() for vertex 0
   if ( (dfs_coloring(0)) <=0 ){
     printf("Solution does not exist\n");
     return -1;
   }
//    if ( (coloring_CSP_constraint(vertex_hightest_deg,0)) <=0 ){
//     printf("Solution does not exist\n");
//     return -1;
//   }
  
  // if there is a solution for N colors
  printSolution();
  fclose(fp);
  return 0;
}


int isSafe_adjList(int v,  int c)
{
  int i,u;

  for(i=0;i<adj_list[v].degre;i++){
    u = adj_list[v].nbrs[i];
    if(color[u] == c)
      return -1;
  }
  return 1;
  
}
int isSafe_matrix(int v,  int c)
{
  for (int i = 0; i < N; i++){
      if (adj_mtx[v][i] && c == color[i]){
          return -1; // false
        }   
  }
  return 1;
}

int dfs_coloring(int v)
{
  if (v == N) // if all vertices has been colored
      return 1;

  /* Consider this vertex v and try different colors */
  for (int c = 0; c < COLORS; c++){
      /* Check if assignment of color c to v is fine*/
      if (isSafe_adjList(v, c) >0)
      {
         color[v] = c;

         /* recur to assign colors to rest of the vertices */
         if (dfs_coloring(v+1) >0 )
           return 1;

          /* If assigning color c doesn't lead to a solution
             then remove it */
         color[v] = NO_COLOR;
      }
  }
  /* If no color can be assigned to this vertex then return false */
  return -1;
}

// start by picking up the node with highest degre
int coloring_CSP_constraint(int v, int deph)
{
  if (deph == N) // if all vertices has been colored
      return 1;

  /* Consider this vertex v and try different colors */
  for (int c = 0; c < COLORS; c++){
    // first, check if c is available to v
    if(isColorAvailable(v,c) >0){

      color_arc[v][0] = c;
      // Unset bit - Color no longer available
      color_arc[v][1] = (color_arc[v][1] & ~(1 << (c - 1)));

      // now, for each neighbor of v, call arc consistency
      // if any gets to an empty domain, there's no solution for the problem

      // call function again for next good vertex to explore
      coloring_CSP_constraint(pick_next_vertex(), deph++);

      
      /* If assigning color c doesn't lead to a solution
        then remove it */
      color_arc[v][0] = NO_COLOR;
      color_arc[v][1] |= 1<< c; // reset the bit 1 again
    }
    
  }

  /* If no color can be assigned to this vertex then return false */
  return -1;
}

/* A utility function to print solution */
void printSolution()
{
  printf("The solution for the problem is:\n");
  for (int i = 0; i < N; i++)
    printf(" %d ", color[i]);
  printf("\n");
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

int pick_next_vertex()
{
  int i=0, lower_colors=COLORS, vertex =0;
  int num_aval_colors = COLORS;
  for (i = 0; i < N; i++){
    if(color_arc[i][0] == NO_COLOR){ // if node hasn't been colored
      num_aval_colors = how_many_bits_sets(color_arc[i][1]);
      if ( num_aval_colors < lower_colors ){
        lower_colors = num_aval_colors;
        vertex = i;
      }
    }
  }

  return vertex;
}

int isColorAvailable(int v, int c)
{
  return (v & (1 << c) );
}
int how_many_bits_sets(int num)
{
  int result =0;
  for (int i = 0; i < COLORS; i++){
    if (num & (1 << i) )
      result++;
  }

  return result;
}
int highest_degree()
{
  int i, highest = 0;
  for (i = 0; i < N; i++)
    highest = adj_list[i].degre > highest ? adj_list[i].degre:highest;
  
  return highest;
}
void init_adjList()
{
  adj_list = malloc(N* sizeof(ADJ_LIST));
  
  for(int i=0;i<N;i++){
    adj_list[i].degre  = 0;
    adj_list[i].size = 0;
    adj_list[i].nbrs = 0;  // null pointer
  }
  
}
void init_vertex(char * filename)
{
  char str[10];
  int index =0;
  for(int i=0; filename[i] ; i++){
    if(isdigit(filename[i])){
      str[index++] = filename[i];
    }
  }
  N = atoi(str);
}

void init_colors()
{

  color = malloc(N* sizeof(int *));

  for(int i=0; i<N; i++)
      color[i] = NO_COLOR; // no color set yet

}
void init_color_arc()
{

  int i,j;
  color_arc = malloc(N* sizeof(int *)); // N rowns 

  // allocate memory for the colum
  for(j=0; j<N; j++)
      color_arc[j] = malloc(COLUMNS * sizeof(int)); // 2 columns

  // initialize with a number that has all |COLORS| positions set to 1
  // for 3 colors for example, that would be 7 --> 111

  int color_set = COLORS - (COLORS -1) >0 ? 1:0;
  for (i = 2, j=1; j < COLORS; i*=2, j++)
    color_set += i;

  for(i=0; i<N; i++){
    for(j=0; j<COLUMNS; j++){
      color_arc[i][j] = j>0 ? color_set:NO_COLOR; // first colum gets NO_COLOR set, second receives initial available colors
    }
  }
}
void init_matrix()
{

  adj_mtx = malloc(N* sizeof(int *));

  // allocate memory for the matrix
  for(int j=0; j<N; j++)
      adj_mtx[j] = malloc(N * sizeof(int));

  // initialize to 0
  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      adj_mtx[i][j] = 0;
    }
  }
}

void print_matrix()
{
  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      printf("%d ",adj_mtx[i][j]);
    }
    printf("\n");
  }
  
}
