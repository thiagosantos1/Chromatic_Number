#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h> 


#define COLORS_FIXED		 4 // size of the adjacency Matrix
#define X		 255 // Max size of a line in a file
#define NO_COLOR	-1
#define CHUNK  		16
#define COLUMNS   2

const char * COLOR_USED[10]={"Red", "Blue", "Green", "Black", "White", "Yellow", "Grey", "Cyan", "Pink", "Purple"};
int COLORS = 0;

// define a struct to be use as adjacency list
typedef struct
{
  int degre; // to now how many neighors this vertex has / size of the linked list
  int size;   // how many itens allocated
  int * nbrs; // represents which vertex are its neighbors
  //int num_aval_colors; // save how many colors is available for that vertex
} ADJ_LIST;


short * *adj_mtx; // 0-1 if both nodes has an edge // gonna alocate 
short * *color_arc; // matrix Nx2 that has the color assigned and the colors remainings for each node
short * *backup_color; // matrix NxN to hold a backup for each state(vertex), that way you can come back to the orig
ADJ_LIST * adj_list;
short N;        // number of vertexes // dinymic allocated, based on the name of the program

void init_vertex(char * filename); // initialize N, that represents how many vertex in the graph
void init_adjList(); // initialize the adj list array
void init_matrix();

// function to initialize the color_arc matrix, that works with forward checking CSP constraint
void init_color_arc();
void init_backup_color();
int coloring_CSP_constraint(int v, int deph);
void printSolution_CSP();

int how_many_bits_sets(int num); // return how many bits are set in a number // how many colors available
int highest_degree(); 
int pick_next_vertex(); // pick the vertex in the graph that has the minimum num of available colors 

int domain_reduction(int vertex, int color); // run domain reduction for all neighbors of vertex
int isColorAvailable(int v, int c); // check if color c is available(if bit is set at that c position)
void update_alist(int u, int v);

void backup_status(int v); // on color_arc[0 to N][1], copy what is on backup_color[v]
void return_status(int v); // return the status to color_arc, from what it was when v got a color and made a backup

int foundSolution(); // search to check if all vertices has been colored

int main(int argc, char * argv[])
{
  if(argc<3){
    fprintf(stderr, "\nFile name <%s usage> file.nums && number of available colors\n", argv[0]);
    return 0;
  }
  COLORS = atoi(argv[2]);
  if(COLORS <1){
    fprintf(stderr, "No solutions for %d colors\n", COLORS);
    return 0;
  }
  
  init_vertex(argv[1]); // initialize how many vertex there are in the graph, based on the name of the file
  init_matrix();
  init_adjList();
  init_color_arc();
  
  char * filename = argv[1];
  FILE * fp = fopen(filename, "r");
  if(fp == NULL){
    fprintf(stderr, "\nError opening the file\n");
    exit(0);
  }
  int class1, class2;


  while( fscanf(fp,"%d %d", &class1, &class2) == 2){
   
    // add arc 
    adj_mtx[class1][class2] = 1;
    adj_mtx[class2][class1] = 1;
    
    update_alist(class1,class2);
    update_alist(class2,class1);
    
  }

  // save the vertex with more degrees, to start the search
  int vertex_hightest_deg = highest_degree();

   if ( (coloring_CSP_constraint(vertex_hightest_deg,0)) <=0 ){
    fprintf(stderr, "\nSolution does not exist for %d colors\n", COLORS);
    return -1;
  }
  
  // if there is a solution for N colors
  printSolution_CSP();
  fprintf(stderr, "\nThere is a Solution for %d colors\n\n", COLORS);
  fclose(fp);
  return 0;
}



// start by picking up the node with highest degre
int coloring_CSP_constraint(int v, int deph)
{
  if (foundSolution() >0){ // if all vertices has been colored
      return 1;
  }

  /* Consider this vertex v and try different colors */
  for (int c = 0; c < COLORS; c++){
    // first, check if c is available to v
    if(isColorAvailable(v,c) >0){

      backup_status(v); // backup the status of all vertices to v
      color_arc[v][0] = c;

      // Unset bit - Color no longer available
      color_arc[v][1] = (color_arc[v][1] & ~(1 << c ));

      // now, for each neighbor of v, call domain_reduction
      // if any gets to an empty domain, there's no solution for the problem
      if(domain_reduction(v,c) <0){ // if any of the neighbors got empty relation 
         return_status(v); // since this color c did not work, come back the backup before reduction
         return -1;
      }
      
      // call function again for next good vertex to explore
      if( coloring_CSP_constraint(pick_next_vertex(), deph+=1) >0){
	       return 1;
      }

      /* If assigning color c doesn't lead to a solution
        then remove it */
      // has to undo for all neighbors
      return_status(v); // since this color c did not work, come back the backup before reduction
      color_arc[v][0] = NO_COLOR;
      color_arc[v][1] |= 1<< c; // reset the bit 1 again
    }
    
  }
  
  /* If no color can be assigned to this vertex then return false */
  return -1;

}

// back up only the neighbors of Vertex
void backup_status(int vertex)
{

  for(int i = 0; i < adj_list[vertex].degre; i++)
    backup_color[vertex][ adj_list[vertex].nbrs[i] ] = color_arc[ adj_list[vertex].nbrs[i] ][COLUMNS-1];
}

void return_status(int vertex)
{

   for(int i = 0; i < adj_list[vertex].degre; i++)
    color_arc[ adj_list[vertex].nbrs[i] ][COLUMNS-1] = backup_color[vertex][ adj_list[vertex].nbrs[i] ];

  color_arc[vertex][COLUMNS-2] = NO_COLOR;
}

int foundSolution()
{
  for (int i = 0; i < N; i++){
    if(color_arc[i][COLUMNS-2] == NO_COLOR)
      return -1;
  }
  return 1;
}

void printSolution_CSP()
{
  printf("\n\t*** The solution for the problem is ***\n\n");
  for (int i = 0; i < N; i++)
    fprintf(stderr,"Vertex %d got colored with %s\n", i, COLOR_USED[ color_arc[i][COLUMNS-2] ]);
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

int how_many_bits_sets(int num)
{
  int result =0;
  for (int i = 0; i < COLORS; i++){
    if (num & (1 << i) )
      result++;
  }

  return result;
}

int domain_reduction(int vertex, int color)
{
  int i, neighbor_index;
  for(i=0; i< adj_list[vertex].degre; i++){ // to go through all neighbors
    neighbor_index = adj_list[vertex].nbrs[i];
    // set color to unavailable
    color_arc[neighbor_index][COLUMNS-1] = (color_arc[neighbor_index][COLUMNS-1] & ~(1 << color ));
    if( (color_arc[neighbor_index][COLUMNS-1] <1) &&  (color_arc[neighbor_index][COLUMNS-2] ==NO_COLOR ) ) // if there's no more color available
      return -1;
  }
  return 1; // no problem so far
}
int isColorAvailable(int v, int c)
{
  return (color_arc[v][COLUMNS-1] & (1 << c) );
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
  char *substr = "problem";
  char *result = strstr(filename, substr);
  int pos = result - filename;
  
  char str[20];
  int index =0;
  for(int i=pos; filename[i] ; i++){
    if(isdigit(filename[i])){
      str[index++] = filename[i];
    }
  }
  N = atoi(str);
}

void init_color_arc()
{

  int i,j;
  color_arc = malloc(N* sizeof(short *)); // N rowns 

  // allocate memory for the colum
  for(j=0; j<N; j++)
      color_arc[j] = malloc(COLUMNS * sizeof(short)); // 2 columns

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


  init_backup_color();
}

void init_backup_color()
{
  int i,j;
  backup_color = malloc(N* sizeof(short *)); // N rowns 

  // allocate memory for the columns of each backup vertex
  for(j=0; j<N; j++)
      backup_color[j] = malloc(N * sizeof(short)); 

  for(i=0; i<N; i++){
    for(j=0; j<N; j++){
      backup_color[i][j] = color_arc[0][1]; // all starts with the same valeu of available colors
    }
  }
}
void init_matrix()
{

  adj_mtx = malloc(N* sizeof(short *));

  // allocate memory for the matrix
  for(int j=0; j<N; j++)
      adj_mtx[j] = malloc(N * sizeof(short));

  // initialize to 0
  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      adj_mtx[i][j] = 0;
    }
  }
}


