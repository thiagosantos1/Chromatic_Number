
#include <python3.6m/Python.h>

typedef
  unsigned char
uchar;

#define SIZE 1024

int allocate(int n, int nc);
void setup(uchar color[]);
void addedge(int u, int v);
void deallocate(void);
int dfs(int dep, uchar color[]);
int processAdjlist(PyObject *it, int **pli);
int processEdgelist(PyObject *it, int **pli);

static PyObject *py_ThreeColor(PyObject *self, PyObject *args, PyObject *givenkeys)
{
  PyObject *pylist;
  PyObject *alistobj = 0,*elistobj = 0,*it;
  int i, n, flag;
  uchar *color;
  int *li;
  static char *keys[] = {"adjlist", "edgelist", NULL};

  if(!PyArg_ParseTupleAndKeywords(args, givenkeys, "|OO", keys, &alistobj, &elistobj)){
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
  if(!allocate(n, 3)){                 // note the 3
    fprintf(stderr,"PyObject_GetIter\n");
    return Py_False;
  }
  color = malloc(n * sizeof(uchar));
  setup(color);
  for(i = 0 ; li[i] >= 0 ; i += 2)
    addedge(li[i],li[i+1]);
  flag = dfs(1, color);
  pylist = PyList_New(0);
  if(flag > 0){
    for(i = 0 ; i < n ; i++)
      PyList_Append(pylist, PyLong_FromLong((long) color[i]));
  }
  deallocate();
  free(color);
  free(li);
  return pylist;
}

static PyMethodDef cs670Methods[]={
  {"ThreeColor", (PyCFunction) py_ThreeColor, METH_VARARGS | METH_KEYWORDS, "Tries to 3-color a graph."},
  {0,0,0,0}
};

static struct PyModuleDef cs670mod = {
  PyModuleDef_HEAD_INIT,
  "cs670mod",
  "Find 3-coloring of graph",
  -1,
  cs670Methods
};

PyMODINIT_FUNC
PyInit_cs670mod(void)
{
  return PyModule_Create(&cs670mod);
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
