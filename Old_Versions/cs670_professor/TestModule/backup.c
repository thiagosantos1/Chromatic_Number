
#include <python3.5m/Python.h>

static PyObject *py_adjlist(PyObject *self, PyObject *args)
{
  PyObject *ob,*it,*sob;
  long count, n;

  if(!PyArg_ParseTuple(args,"O",&ob)){
    fprintf(stderr,"PyArg_ParseTuple error\n");
    return 0;
  }
  it = PyObject_GetIter(ob);
  if(!it){
    fprintf(stderr,"PyObject_GetIter\n");
    return 0;
  }
  count = 0;
  while((sob = PyIter_Next(it))){
    n = PyLong_AsLong(sob);
    count++;
    printf("%ld  %ld\n", count, n);
  }
  return PyLong_FromLong(count);
}

static PyMethodDef cs670Methods[]={
  {"adjlist", py_adjlist, METH_VARARGS, "Adjacency List"}
};

static struct PyModuleDef cs670mod = {
  PyModuleDef_HEAD_INIT,
  "cs670mod",
  "Pass adjacency list",
  -1,
  cs670Methods
};

PyMODINIT_FUNC
PyInit_cs670mod(void)
{
  return PyModule_Create(&cs670mod);
}

