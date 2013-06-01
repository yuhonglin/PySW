/**
 * @file   sw.cpp
 * @author yuhonglin <yuhonglin1986@gmail.com>
 * @date   Sat Jun  1 19:00:39 2013
 * 
 * @brief  wrap the algorithm into a python package
 * 
 * 
 */

#include <Python.h>  
#include "swalign.h"
CSWAlign *_align;
extern "C" PyObject*  sw_setfoo(PyObject *self, PyObject *args)  
{
  PyObject *listobj;
  if(!PyArg_ParseTuple(args, "O!", &PyList_Type, &listobj)){
    return NULL;
  }
  int length = PyList_Size(listobj);
  int *foostr = new int[length];
  for(int i=0; i<length; i++){
    foostr[i] = PyInt_AsLong(PyList_GetItem(listobj, i));
  }
  _align->setfoo(foostr, length);
  delete foostr;
  Py_DECREF(listobj);
  Py_RETURN_NONE;
} 

extern "C" PyObject*  sw_setbar(PyObject *self, PyObject *args)  
{   
  PyObject *listobj;
  if(!PyArg_ParseTuple(args, "O!", &PyList_Type, &listobj)){
    return NULL;
  }
  int length = PyList_Size(listobj);
  int *barstr = new int[length];
  for(int i=0; i<length; i++){
    barstr[i] = PyInt_AsLong(PyList_GetItem(listobj, i));
  }
  _align->setbar(barstr, length);
  delete barstr;
  Py_DECREF(listobj);
  Py_RETURN_NONE;
} 

extern "C" PyObject*  sw_compare(PyObject *self)  
{
  _align->calculate();
  
  int length = _align->getmatchlength();
  const int *matchstr =  _align->getmatchstr();
  const int *foomatchindex = _align->getfoomatchindex();
  const int *barmatchindex = _align->getbarmatchindex();

  int i=0;
  
  PyObject* match_str = PyList_New(length);
  for(i=0; i<length; i++){
    PyList_SetItem(match_str, i, Py_BuildValue("i", matchstr[i]));
  }
  
  PyObject* foo_match_index = PyList_New(length);
  for(i=0; i<length; i++){
    PyList_SetItem(foo_match_index, i, Py_BuildValue("i", foomatchindex[i]));
  }
    
  PyObject* bar_match_index = PyList_New(length);
  for(int i=0; i<length; i++){
    PyList_SetItem(bar_match_index, i, Py_BuildValue("i", barmatchindex[i]));
  }

  PyObject* resultuple = PyTuple_New(3);
  PyTuple_SetItem(resultuple, 0, match_str);
  PyTuple_SetItem(resultuple, 1, foo_match_index);
  PyTuple_SetItem(resultuple, 2, bar_match_index);
 
  return resultuple;
} 

extern "C" PyObject* sw_dump(PyObject *self)
{
  _align->dump();

  Py_RETURN_NONE;
}


extern "C" PyObject* sw_setscore(PyObject *self, PyObject *match)
{
  
  int a, b, c;
  PyArg_ParseTuple(match, "iii", &a, &b, &c);
  _align->setScore(a, b, c);
 
  Py_RETURN_NONE;
}


PyMethodDef sw_methods[] = {  
  {"setfoo", (PyCFunction)sw_setfoo, METH_VARARGS | METH_KEYWORDS, "set foo string"},
  {"setbar", (PyCFunction)sw_setbar, METH_VARARGS | METH_KEYWORDS, "set bar string"},  
  {"compare", (PyCFunction)sw_compare, METH_VARARGS | METH_KEYWORDS, "compare the strings"},  
  {"dump", (PyCFunction)sw_dump, METH_VARARGS | METH_KEYWORDS, "print the information of the result"},  
  {"setscore", (PyCFunction)sw_setscore, METH_VARARGS | METH_KEYWORDS, "set the score"},
  {NULL, NULL, 0, NULL}  
};  
  
extern "C" void initsw(void)  
{  
  Py_InitModule("sw", sw_methods);
  _align = new CSWAlign;
}
