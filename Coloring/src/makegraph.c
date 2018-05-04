
#include <findcolor.h>

int makegraph(GRAPH *op, USER_PARAMS *ip)
{
  int i,j,k;
  int N, nedges,tmp;
  int maxdeg=0;
  FILE *fd;

  fd = fopen(ip->filename,"r");
  if(!fd)
    return -1;
  N = op->order = ip->order;

  op->maxdegree = 0;

// allocate space for matrix
  op->a   = malloc(N*sizeof(uchar *));
  op->deg = malloc(N*sizeof(int));
  memset(op->deg, 0, N * sizeof(int));
  for(i=0;i<N;i++)
    op->a[i] = malloc(N*sizeof(uchar));
  
// allocate space for adj list
  op->adj_list = malloc(N* sizeof(ADJ_LIST));
  
  for(int i=0;i<N;i++){
    op->adj_list[i].nbrs = 0;  // null pointer
  }
// read matrix
  nedges = 0;
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      fscanf(fd,"%1d",&k); 
      op->a[i][j] = k;
      if(i < j && k == 1){  // add each edge once
      	// insert in adj list
      	if(op->deg[i] == 0){
      	  op->adj_list[i].nbrs = (int*)malloc(1 * sizeof(int));
        }
      	else{
      	  tmp = op->deg[i];
      	  op->adj_list[i].nbrs = (int*)realloc(op->adj_list[i].nbrs, (tmp+1) * sizeof(int));
      	}
      	
      	if(op->deg[j] == 0){
      	  op->adj_list[j].nbrs = (int*)malloc(1 * sizeof(int));
        }
      	else{
      	  tmp = op->deg[j];
      	  op->adj_list[j].nbrs = (int*)realloc(op->adj_list[j].nbrs, (tmp +1) * sizeof(int));
      	}
      
      	op->adj_list[i].nbrs[op->deg[i]] = j;
      	op->adj_list[j].nbrs[op->deg[j]] = i;
      	
        op->deg[i]++;
        op->deg[j]++;
        if(op->deg[i] > maxdeg){
          maxdeg = op->deg[i];
          op->vertex_max_degre = i;
        }

        if(op->deg[j] > maxdeg){
          maxdeg = op->deg[j];
          op->vertex_max_degre = j;
        }

        nedges++;
      }
    }
  }
  op->maxdegree = maxdeg;

  fclose(fd);
// allocate space for edgelist and coloring

  op->elist = malloc(2 * nedges * sizeof(int));
  op->size = nedges;
  op->coloring = malloc(N * sizeof(int));  
  op->available_colors = malloc(N * sizeof(int));  
  op->is_graph_connected = 1; // initialize to yes
  return 0;

}

