
#include <Python.h>

#include <ctype.h>

static PyObject *ab(PyObject *self)
{
   printf("Hello.\n");
   Py_RETURN_NONE;
}

static PyObject *cd(PyObject *self)
{
   printf("Goodbye.\n");
   Py_RETURN_NONE;
}

static PyObject *ef(PyObject *self, PyObject *args)
{
   char *s;
   int i;

   if (!PyArg_ParseTuple(args, "s", &s)) {
      return NULL;
   }
   for(i=0;i < (int) strlen(s);i++)
     s[i] = islower(s[i]) ? ('a' + (s[i] - 'a' + 1) % 26) : ' ';

   return Py_BuildValue("s",s);
}

static PyMethodDef module_methods[] = {
   { "ab", (PyCFunction) ab, METH_NOARGS,  "Prints Hello." },
   { "cd", (PyCFunction) cd, METH_NOARGS,  "Prints Goodbye." },
   { "ef", (PyCFunction) ef, METH_VARARGS, "Encodes strings." },
   { NULL, NULL, 0, NULL }
};

static struct PyModuleDef abmod = {
  PyModuleDef_HEAD_INIT,
  "ab",
  "Does nothing: ab, cd, ef.",
  -1,
  module_methods
};

PyMODINIT_FUNC PyInit_ab(void)
{
  return PyModule_Create(&abmod);
}


