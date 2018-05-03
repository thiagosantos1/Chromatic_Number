
#include <findcolor.h>


int dfs_bipartite_check(int vertex, int color,GRAPH *op); 
int get_vertex_not_colored(int N_vertices,GRAPH *op); // return a vertex that did not get colored after dfs, if exists

int bipartite(GRAPH *op)
{
  int vertex =0, compontent=1, result = 0, vertex_not_colered = -1;
  int n = op->order;
  for(int i=0;i<n;i++)              // not yet colored
    op->coloring[i] = NOCOLOR;
    
  for(;;){ // make sure it runs until cover all edges
    result = dfs_bipartite_check(vertex, Color_1, op);
    if(result <=0){ // you are then sure it's not bipartite
      return -1; //Graph is not bipartite
    }
    
    else{ // it may be a disconected graph. Then, it may be a false positive
      
      // then, check if everybody got a color. If so, you are sure it's bipartite. If not, have to run again the dfs
      // from that node withot a color
      vertex_not_colered = get_vertex_not_colored(n,op);
      if(vertex_not_colered >=0){
      	printf("Graph is not connected, running dfs again for compontent %d and vertex %d.....\n",++compontent, vertex_not_colered);
      	vertex = vertex_not_colered;
        op->is_graph_connected = 1;
      }
      else{ // you are then sure that everybody got colored and it's bipartite
	     return 1; //Graph is bipartite
      }
      
    }
  }
  return 1;
}


int dfs_bipartite_check(int vertex, int color,GRAPH *op)
{
  int vert_ngbr, flag=1,i;
  
  op->coloring[vertex] = color;
  color = color==Color_1 ? Color_2:Color_1;
  
  for(i=0; i<op->deg[vertex]; i++){
    vert_ngbr = op->adj_list[vertex].nbrs[i];
    if(op->coloring[vert_ngbr] == NOCOLOR){
      flag = dfs_bipartite_check(vert_ngbr,color,op);
      if(flag<=0)
	break;
    } else if(op->coloring[vert_ngbr] == op->coloring[vertex]){
    
      return 0;
    }
  }
  
  return flag;
}

int get_vertex_not_colored(int N_vertices,GRAPH *op)
{
  for(int i=0; i< N_vertices; i++){
    if(op->coloring[i] == NOCOLOR)
      return i;
  }
  
  return -1;
  
}
