#include <Python.h>
#include <miniqbt/MiniQbt.hpp>




static int _test(int i){
	return i + 20;
}

static PyObject* testMethod(PyObject* self, PyObject* args){
    auto inp = 0;
    //https://docs.python.org/2.0/ext/parseTuple.html
    if(!PyArg_ParseTuple(args, "i", &inp)){ //parse de variabel naar integer
        return nullptr;
    }
    return Py_BuildValue("i", _test(inp)); //geef het terug (als integer)
}


static PyMethodDef TestMethods[] = {
    {"testMethod",//Naam van de methode oproepbaar van python
        testMethod,//Function pointer
        METH_VARARGS,
        "doet plus een bij de input"//uitleg van de methode
    },
    {nullptr,nullptr,0,nullptr}
}; 


static struct PyModuleDef testModuleMethods = {
  PyModuleDef_HEAD_INIT,
  "testModule",
  "",
 -1,
  TestMethods
};


PyMODINIT_FUNC PyInit_MiniQbtNative(void)
{
    return PyModule_Create(&testModuleMethods);
}
