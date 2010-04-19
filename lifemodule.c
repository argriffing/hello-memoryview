#include <Python.h>

static PyObject *LifeError;

static PyObject *
step_python (PyObject *self, PyObject *args)
{
  /* read the args */
  PyObject *obj_source;
  PyObject *obj_sink;
  int ok = PyArg_ParseTuple(args, "OO", &obj_source, &obj_sink);
  if (!ok) goto end;
  /* read the vector of likelihoods */
  /*
  Py_ssize_t nlikelihoods;
  double *l_big = double_vector_helper(ltuple, &nlikelihoods);
  if (!l_big)
  {
    PyErr_SetString(HmmuscError, "likelihood init error");
    goto end;
  }
  */
  /*
  dtuple = PyTuple_New(nlikelihoods);
  Py_ssize_t i;
  for (i=0; i<nlikelihoods; i++)
  {
    PyTuple_SetItem(dtuple, i, PyFloat_FromDouble(d_big[i]));
  }
  */
end:
  return Py_BuildValue("i", 42);
}

static PyMethodDef LifeMethods[] = {
  {"step", step_python, METH_VARARGS,
    "Do one generation of the Conway Game of Life cellular automaton."},
  {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC
initlife(void) 
{
  PyObject *m = Py_InitModule("life", LifeMethods);
  if (!m) return;

  LifeError = PyErr_NewException("life.error", NULL, NULL);
  Py_INCREF(LifeError);
  PyModule_AddObject(m, "error", LifeError);
}

