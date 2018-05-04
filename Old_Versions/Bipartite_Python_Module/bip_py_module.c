#include <python3.5m/Python.h>

#define SIZE 1024
#define Color_1 	1
#define Color_2		2

void init_vertex(int num_vert); 
void init_adjList(void); 
void update_alist(int u, int v);
void display_graph(void);
int get_vertex_not_colored(void); 
int bad_neighbors(int vertex); 
int dfs_bipartite_check(int vertex, int color); 
int processAdjlist(PyObject *it, int **pli);
int processEdgelist(PyObject *it, int **pli);

static PyObject *py_isBipartite(PyObject *self, PyObject *args, PyObject *givenkeys)
{
  PyObject *alistobj = 0,*elistobj = 0,*it;
  int i, n, *li;
  static char *keys[] = {"adjlist", "edgelist", NULL};
  if(!PyArg_ParseTupleAndKeywords(args, givenkeys, "|OO", keys, &alistobj, &elistobj)){
   //if(!PyArg_ParseTupleAndKeywords(args, givenkeys, "|OO", keys,  &elistobj)){
    fprintf(stderr,"PyArg_ParseTuple error\n");
    return 0;
  }
  
  if(alistobj){
    it = PyObject_GetIter(alistobj);
    fprintf(stderr,"An adjacency list.\n");
    n = processAdjlist(it, &li);
  } else if(elistobj){
    it = PyObject_GetIter(elistobj);
    fprintf(stderr,"An edge list.\n");
    n = processEdgelist(it, &li);
  } else {
    return Py_False;
  }
  
  if(!it){
    fprintf(stderr,"PyObject_GetIter\n");
    return Py_False;
  }
  
 // fprintf(stderr,"vertices %d\n",n);
  init_vertex(n);
  init_adjList();
  
  // for elist
  for(i = 0 ; li[i] >= 0 ; i+=2){
    //fprintf(stderr,"i %d v%d & u %d\n",i, li[i],li[i+1]);
    update_alist(li[i],li[i+1]);
    update_alist(li[i+1],li[i]);
  }
  
  // check for all vertex(even not connected graphs
  int vertex =0, compontent=1, result = 0, vertex_not_colered = -1, isBip = -1;
  
  for(;;){ // make sure it runs until cover all edges
    result = dfs_bipartite_check(vertex, Color_1);
    if(result <=0){ // you are then sure it's not bipartite
      isBip = -1;
      break;
    }
    
    else{ // it may be a disconected graph. Then, it may be a false positive
      
      // then, check if everybody got a color. If so, you are sure it's bipartite. If not, have to run again the dfs
      // from that node withot a color
      vertex_not_colered = get_vertex_not_colored();
      if(vertex_not_colered >=0){
	fprintf(stderr,"Graph is not connected, running dfs again for compontent %d and vertex %d.....\n",++compontent, vertex_not_colered);
	vertex = vertex_not_colered;
      }
      else{ // you are then sure that everybody got colored and it's bipartite
	isBip = 1;
	break;
      }
      
    }
  }
  
  return isBip > 0 ? Py_True:Py_False;
  
}

static PyMethodDef bip_Methods[]={
  {"isBipartite", (PyCFunction) py_isBipartite, METH_VARARGS | METH_KEYWORDS, "Finds if graph is bipartite or not"},
  {0,0,0,0}
};

static struct PyModuleDef bip_module = {
  PyModuleDef_HEAD_INIT,
  "bip_module",
  "Finds if graph is bipartite or not",
  -1,
  bip_Methods
};

PyMODINIT_FUNC
PyInit_bip_module(void)
{
  return PyModule_Create(&bip_module);
}

int processAdjlist(PyObject *it, int **pli)
{
  PyObject *sob, *ssob, *sit;
  int *li;
  int nitems;
  long u,v,size;

  size = SIZE;
  li = *pli = malloc(size*sizeof(int));
  nitems = 0;
  u = 0;
  while((sob = PyIter_Next(it))){
    sit = PyObject_GetIter(sob);
    while((ssob = PyIter_Next(sit))){
      v = PyLong_AsLong(ssob);
      if(nitems >= size-2){
        size <<= 1;
        li = realloc(li,size*sizeof(int));
      }
      if(u < v){
        li[nitems++] = (int) u;
        li[nitems++] = (int) v;
      }
    }
    u++;
  }
  li[nitems] = -1;
  return u;
}

int processEdgelist(PyObject *it, int **pli)
{
  PyObject *sob, *ssob, *sit;
  int *li;
  int nitems;
  long u,v,n,size;

  n = 0;
  size = SIZE;
  li = *pli = malloc(size*sizeof(int));
  nitems = 0;
  while((sob = PyIter_Next(it))){
    sit = PyObject_GetIter(sob);
    ssob = PyIter_Next(sit);
    u = PyLong_AsLong(ssob);
    ssob = PyIter_Next(sit);
    v = PyLong_AsLong(ssob);
    if(nitems >= size-2){
      size <<= 1;
      li = realloc(li,size*sizeof(int));
    }
    li[nitems++] = (int) u;
    li[nitems++] = (int) v;
    if(u > n) n = u;
    if(v > n) n = v;
  }
  li[nitems] = -1;
  return (int)(n + 1);
}
