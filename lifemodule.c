#include <Python.h>

static PyObject *LifeError;

/* One generation of Conway Life.
 */
int do_one_generation(long *source, long *sink, int nrows, int ncols)
{
  int row, col;
  int index = 0;
  for (row=0; row<nrows; ++row) {
    for (col=0; col<ncols; ++col, ++index) {
      /* get the source value and the number of neighbors for this position */
      int value = source[index];
      int dr, dc;
      int nneighbors = 0;
      for (dr=-1; dr<2; ++dr) {
        for (dc=-1; dc<2; ++dc) {
          if (dr || dc) {
            int r = row + dr;
            int c = col + dc;
            if (r == nrows) {
              r = 0;
            } else if (r == -1) {
              r = nrows - 1;
            }
            if (c == ncols) {
              c = 0;
            } else if (c == -1) {
              c = ncols -1;
            }
            nneighbors += source[r*ncols + c];
          }
        }
      }
      /* set the sink value according to the source value and the neighbors */
      int next_value = 0;
      if (value && (nneighbors == 2 || nneighbors == 3)) {
        next_value = 1;
      } else if (!value && nneighbors == 3) {
        next_value = 1;
      }
      sink[index] = next_value;
    }
  }
  return 0;
}

static PyObject *
step_python (PyObject *self, PyObject *args)
{
  int except = 0;
  /* buffer views */
  Py_buffer source_view;
  Py_buffer sink_view;
  int got_source_view = 0;
  int got_sink_view = 0;
  /* read the args */
  PyObject *obj_source;
  PyObject *obj_sink;
  if (!PyArg_ParseTuple(args, "OO", &obj_source, &obj_sink)) {
    except = 1; goto end;
  }
  /* both objects should support the buffer interface */
  if (!PyObject_CheckBuffer(obj_source)) {
    PyErr_SetString(LifeError,
        "the source object does not support the buffer interface");
    except = 1; goto end;
  }
  if (!PyObject_CheckBuffer(obj_sink)) {
    PyErr_SetString(LifeError,
        "the sink object does not support the buffer interface");
    except = 1; goto end;
  }
  /* get the buffer view for each object */
  int flags = PyBUF_ND | PyBUF_FORMAT | PyBUF_C_CONTIGUOUS | PyBUF_WRITABLE;
  if (PyObject_GetBuffer(obj_source, &source_view, flags) < 0) {
    except = 1; goto end;
  } else {
    got_source_view = 1;
  }
  if (PyObject_GetBuffer(obj_sink, &sink_view, flags) < 0) {
    except = 1; goto end;
  } else {
    got_sink_view = 1;
  }
  /* each buffer should be two dimensional */
  if (source_view.ndim != 2) {
    PyErr_SetString(LifeError, "the source buffer should be 2D");
    except = 1; goto end;
  }
  if (sink_view.ndim != 2) {
    PyErr_SetString(LifeError, "the sink buffer should be 2D");
    except = 1; goto end;
  }
  /* the buffers should be the same shape */
  if (source_view.shape[0] != sink_view.shape[0] ||
      source_view.shape[1] != sink_view.shape[1]) {
    PyErr_SetString(LifeError,
        "the source and sink buffers should be the same shape");
    except = 1; goto end;
  }
  /* format should be long (l) */
  if (source_view.format[0] != 'l') {
    PyErr_SetString(LifeError, "source buffer format should be long");
    except = 1; goto end;
  }
  if (sink_view.format[0] != 'l') {
    PyErr_SetString(LifeError, "sink buffer format should be long");
    except = 1; goto end;
  }
  /* buffers should be non-null */
  if (source_view.buf == NULL) {
    PyErr_SetString(LifeError, "source buffer is NULL");
    except = 1; goto end;
  }
  if (sink_view.buf == NULL) {
    PyErr_SetString(LifeError, "sink buffer is NULL");
    except = 1; goto end;
  }
  /* get the number of rows and columns */
  int nrows = source_view.shape[0];
  int ncols = source_view.shape[1];
  /* do a generation of conway life */
  do_one_generation(source_view.buf, sink_view.buf, nrows, ncols);
end:
  /* clean up the buffer views */
  if (got_source_view) {
    PyBuffer_Release(&source_view);
  }
  if (got_sink_view) {
    PyBuffer_Release(&sink_view);
  }
  /* return an appropriate value */
  if (except) {
    return NULL;
  } else {
    return Py_BuildValue("i", 42);
  }
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

