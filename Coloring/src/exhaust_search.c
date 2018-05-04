#include <findcolor.h>

int * *backup_color; // matrix NxN to hold a backup for each state(vertex), that way you can come back to the orig
int *coloring_copy;
int COLORS;

void init_default_colors(GRAPH *op);
void init_backup_color(int order);
int coloring_CSP_constraint(GRAPH *op, int v, int vert_colored); 
int isColorAvailable(GRAPH *op,int v, int c);
void backup_status(GRAPH *op, int vertex);
void return_status(GRAPH *op,int vertex);
int domain_reduction(GRAPH *op,int vertex, int color);
int pick_next_vertex(GRAPH *op);
int how_many_bits_sets(int num, int mincolors);

void exh_search(GRAPH *op,USER_PARAMS *ip)
{
  COLORS = op->mincolors;
  init_backup_color(op->order);
  for(;;){
    // gonna try one less color;
    COLORS--;
    init_default_colors(op);

    if( (coloring_CSP_constraint(op, op->vertex_max_degre,0)) <=0){
      fprintf(stderr, "Exhaust Search failed for %d colors\n", COLORS);
      break;
    }else{
      fprintf(stderr, "Exhaust Search succed for %d colors\n", COLORS);
      // copy to original and reset to try one less color
      memcpy(op->coloring, coloring_copy, op->order * sizeof(int));
      memset(coloring_copy, NOCOLOR, op->order*sizeof(int));
      op->mincolors = COLORS;
    }
 
	}
}

void init_backup_color(int order)
{
  // initialize the backup now
  backup_color = malloc(order* sizeof(int *)); // N rowns 

  // initialize coloring copy. used to don't modify the original
  coloring_copy = malloc(order* sizeof(int *)); // N rowns 
  memset(coloring_copy, NOCOLOR, order*sizeof(int));

  // allocate memory for the columns of each backup vertex
  for(int j=0; j<order; j++)
      backup_color[j] = malloc(order * sizeof(int)); 

}

/*
* initialize with a number that has all |COLORS| positions set to 1
* for 3 colors for example, that would be 7 --> 111
*/
void init_default_colors(GRAPH *op)
{
  int i,j,N;
  N = op->order;
  int color_set = COLORS - (COLORS -1) >0 ? 1:0;
  for (i = 2, j=1; j < COLORS; i*=2, j++)
    color_set += i;

  // initial available colors. Set by bit
  for(i=0; i<op->order; i++)
    op->available_colors[i] = color_set;

  for(i=0; i<N; i++){
    for(j=0; j<N; j++){
      backup_color[i][j] = color_set; // all starts with the same valeu of available colors
    }
  }

}

int coloring_CSP_constraint(GRAPH *op, int v,int vert_colored )
{
  if (vert_colored >= op->order){ // if all vertices has been colored
      return 1;
  }else if(v >= op->order || v<0)
    return -1;

  /* Consider this vertex v and try different colors */
  for (int c = 0; c < COLORS; c++){
    // first, check if c is available to v
    if(isColorAvailable(op,v,c) >0){

      backup_status(op,v); // backup the status of all vertices to v
      coloring_copy[v] = c; // set clor
      vert_colored++; // colored

      // Unset bit - Color no longer available
      op->available_colors[v] = (op->available_colors[v] & ~(1 << c ));

      // now, for each neighbor of v, call domain_reduction
      // if any gets to an empty domain, there's no solution for the problem
      if(domain_reduction(op,v,c) <0){ // if any of the neighbors got empty relation 
        return_status(op,v); // since this color c did not work, come back the backup before reduction
        vert_colored--; //uncolored
        return -1;
      }
      
      // call function again for next good vertex to explore
      if( coloring_CSP_constraint(op,pick_next_vertex(op),vert_colored ) >0){
         return 1;
      }

      /* If assigning color c doesn't lead to a solution
        then remove it */
      // has to undo for all neighbors
      return_status(op,v); // since this color c did not work, come back the backup before reduction
      coloring_copy[v] = NOCOLOR;
      op->available_colors[v] |= 1<< c; // reset the bit 1 again
      vert_colored--;
    }
    
  }
  
  /* If no color can be assigned to this vertex then return false */
  return -1;
}

int isColorAvailable(GRAPH *op,int v, int c)
{
  return (op->available_colors[v] & (1 << c) );
}

// back up only the neighbors of Vertex
void backup_status(GRAPH *op, int vertex)
{
  int nbr,i;
  for(i = 0; i < op->deg[vertex]; i++){
    nbr = op->adj_list[vertex].nbrs[i];
    backup_color[vertex][nbr] = op->available_colors[nbr];
  }
}

void return_status(GRAPH *op,int vertex)
{
  int nbr,i;
  for(i = 0; i < op->deg[vertex]; i++){
    nbr = op->adj_list[vertex].nbrs[i];
    op->available_colors[nbr] = backup_color[vertex][nbr];
  }

  coloring_copy[vertex] = NOCOLOR;
}

int domain_reduction(GRAPH *op,int vertex, int color)
{
  int i, nbr;
  for(i=0; i< op->deg[vertex]; i++){ // to go through all neighbors
    nbr = op->adj_list[vertex].nbrs[i];
    // set color to unavailable
    op->available_colors[nbr] = (op->available_colors[nbr] & ~(1 << color ));
    if( (op->available_colors[nbr] <1) &&  (coloring_copy[nbr] ==NOCOLOR ) ) // if there's no more color available
      return -1;
  }
  return 1; // no problem so far
}

int pick_next_vertex(GRAPH *op)
{
  int i=0, vertex =-1,num_aval_colors,lower_colors;
  num_aval_colors = lower_colors = COLORS;

  for (i = 0; i < op->order; i++){
    if(coloring_copy[i] == NOCOLOR){ // if node hasn't been colored
      num_aval_colors = how_many_bits_sets(op->available_colors[i],COLORS);
      if ( num_aval_colors < lower_colors ){
        lower_colors = num_aval_colors;
        vertex = i;
      } 
    }
  }

  return vertex;
}

int how_many_bits_sets(int num, int mincolors)
{
  int result =0;
  for (int i = 0; i < mincolors; i++){
    if (num & (1 << i) )
      result++;
  }

  return result;
}

