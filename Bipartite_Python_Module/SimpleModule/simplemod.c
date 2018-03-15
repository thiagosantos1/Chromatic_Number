
#include <python3.6m/Python.h> 

static PyObject *py_SumList(PyObject *self, PyObject *args)
{
  PyObject *ob,*it,*subob;
  long x, sum;

  if(!PyArg_ParseTuple(args,"O",&ob)){
    fprintf(stderr,"PyArg_ParseTuple error\n");
    return 0;
  }
  it = PyObject_GetIter(ob);
  if(!it){
    fprintf(stderr,"PyObject_GetIter\n");
    return 0;
  }
  sum = 0;
  while((subob = PyIter_Next(it))){
    x = PyLong_AsLong(subob);
    sum += x;
  }
  return PyLong_FromLong(sum);
}

// this stuff below is used when the user imports the module

static PyMethodDef simpleMethods[]={
  {"SumList", py_SumList, METH_VARARGS, "Sum List"}
};

static struct PyModuleDef simplemod = {
  PyModuleDef_HEAD_INIT,
  "simplemod",
  "Sums a list of numbers",
  -1,
  simpleMethods
};

PyMODINIT_FUNC
PyInit_simplemod(void)
{
  return PyModule_Create(&simplemod);
}

