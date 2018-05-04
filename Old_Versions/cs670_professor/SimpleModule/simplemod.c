
#include <python3.5m/Python.h>

#define K  1024

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

static PyObject *py_SumDict(PyObject *self, PyObject *args)
{
  PyObject *ob,*key,*val;
  Py_ssize_t pos = 0;
  PyObject *pstring, *ustring;
  char *cstring;

  if(!PyArg_ParseTuple(args,"O",&ob)){
    fprintf(stderr,"PyArg_ParseTuple error\n");
    return 0;
  }
  if(!ob){
    fprintf(stderr,"PyObject_GetIter\n");
    return 0;
  } else {
    while(PyDict_Next(ob, &pos, &key, &val)){
      pstring = PyObject_Repr(val);
      ustring = PyUnicode_AsEncodedString(pstring, "utf-8", "Error ~");
      cstring = PyBytes_AS_STRING(ustring);
      fprintf(stderr,"item: %s\n", cstring);
    }
  }
  return PyLong_FromLong(23);
}

// this stuff below is used when the user imports the module

static PyMethodDef simpleMethods[]={
  {"SumList", py_SumList, METH_VARARGS, "Sum List"},
  {"SumDict", py_SumDict, METH_VARARGS, "Sum Dictionary"},
};

static struct PyModuleDef simplemod = {
  PyModuleDef_HEAD_INIT,
  "simplemod",
  "Sums lists/dictionaries of numbers",
  -1,
  simpleMethods
};

PyMODINIT_FUNC
PyInit_simplemod(void)
{
  return PyModule_Create(&simplemod);
}

