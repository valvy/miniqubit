#include <Python.h>
#include <miniqbt/MiniQbt.hpp>
#include <vector>
#include <utility> 
#include <string>
#include <iostream>
#include <algorithm>
constexpr char ASYNC_CONSTANT[] = "[MiniQbt Async reference]";
static std::vector<std::pair<int, MiniQbt::QasmAsyncIntepreter*>> asyncIntepreters;

static PyObject* get_version(){
     return Py_BuildValue("s", MiniQbt::VERSION);
}

static PyObject* get_name(){
    return Py_BuildValue("s", MiniQbt::NAME);
}

int getUniqueNumber(){
    static int number = 0;
    return number++;
}

/**
*   Calls a specific intepreter.
*   
*/
static PyObject* qasm_async_intepret(PyObject* self, PyObject* args){
    int reference = 0;
    const char* src;
    const char* command;
    
    if(!PyArg_ParseTuple(args, "(si)s",&command, &reference, &src)){ 
        return nullptr;
    }
    
    for(auto& intepreters : asyncIntepreters){
        if(intepreters.first == reference){
            Py_BEGIN_ALLOW_THREADS
            intepreters.second->intepret(std::string(src));
            Py_END_ALLOW_THREADS
            break;
        }
    }
  
    return Py_BuildValue("");
}

static PyObject* qasm_async_intepreter_has_errors(PyObject* self, PyObject* args){
    int reference = 0;
    const char* command;
    std::string result ="";
    if(!PyArg_ParseTuple(args, "(si)",&command, &reference)){ 
        return nullptr;
    }
    for(auto& intepreters : asyncIntepreters){
        if(intepreters.first == reference){
            return Py_BuildValue("b", intepreters.second->hasErrors());
        }
    }
    return Py_BuildValue("");
}

static PyObject* qasm_async_intepreter_get_registers(PyObject* self, PyObject* args){
    int reference = 0;
    const char* command;
    if(!PyArg_ParseTuple(args, "(si)",&command, &reference)){ 
        return nullptr;
    }
    for(auto& intepreters : asyncIntepreters){
        if(intepreters.first == reference){
            PyObject* result = PyList_New(0);
            for(const std::string& d : intepreters.second->getRegisters()){
                
                PyList_Append(result,Py_BuildValue("s",d.c_str()));
            }
            return result;
        }
    }
    return Py_BuildValue("");
}

static PyObject* qasm_async_intepreter_get_error(PyObject* self, PyObject* args){
    int reference = 0;
    const char* command;
    std::string result ="";
    if(!PyArg_ParseTuple(args, "(si)",&command, &reference)){ 
        return nullptr;
    }
    for(auto& intepreters : asyncIntepreters){
        if(intepreters.first == reference){
            return Py_BuildValue("s", intepreters.second->getError().c_str());
        }
    }
    return Py_BuildValue("");
}

static PyObject* qasm_async_read_classic_register(PyObject* self, PyObject* args){
    int reference = 0;
    const char* name;
    const char* command;
    std::string result ="";
    if(!PyArg_ParseTuple(args, "(si)s",&command, &reference, &name)){ 
        return nullptr;
    }

    for(auto& intepreters : asyncIntepreters){
        if(intepreters.first == reference){
            std::vector<bool> d = intepreters.second->readClassicRegister(std::string(name));
            for(const bool& r : d){
                
                result += std::to_string(r);
            }
            break;
        }
    }

    return Py_BuildValue("s", result.c_str());
}



static PyObject* destroy_qasm_async_intepreter(PyObject* self, PyObject* args){
    int reference = 0;
    const char* command;
    
    if(!PyArg_ParseTuple(args, "(si)",&command, &reference)){ 
        return nullptr;
    }

    asyncIntepreters.erase(
        std::remove_if(asyncIntepreters.begin(), asyncIntepreters.end(), 
        [=](std::pair<int, MiniQbt::QasmAsyncIntepreter*> x) { 
            if(x.first == reference){
                delete x.second;
                return true;
            }
            return false;
        }), asyncIntepreters.end()
    );

    return Py_BuildValue("");
}

static PyObject* init_qasm_async_intepreter(PyObject* self, PyObject* args){
    int nr = getUniqueNumber();     
    asyncIntepreters.push_back(
        std::make_pair(
            nr,
            new MiniQbt::QasmAsyncIntepreter()
        )
    );

    return Py_BuildValue("si",ASYNC_CONSTANT, nr);
}

static void clear_memory(void* mem){
    for(auto& d : asyncIntepreters){
        delete d.second;
    }
    asyncIntepreters.clear();
}


static PyMethodDef MiniQbtMethods[] = {
    {
        "get_version",
        (PyCFunction)get_version,
        METH_NOARGS,
        ""
    },
    {
        "get_name",
        (PyCFunction)get_name,
        METH_NOARGS,
        ""
    },
    {
        "init_qasm_async_intepreter",
        init_qasm_async_intepreter,
        METH_VARARGS,
        "Initializes the asynchronous intepreter"
    },
    {
        "async_intepret",
        qasm_async_intepret,
        METH_VARARGS,
        ""
    },
    {
        "destroy_qasm_async_intepreter",
        destroy_qasm_async_intepreter,
        METH_VARARGS,
        ""
    },
    {
        "qasm_async_read_classic_register",
        qasm_async_read_classic_register,
        METH_VARARGS,
        ""
        
    },
    {
        "qasm_async_intepreter_has_errors",
        qasm_async_intepreter_has_errors,
        METH_VARARGS,
        ""
    },
    {
        "qasm_async_intepreter_get_error",
        qasm_async_intepreter_get_error,
        METH_VARARGS,
        ""
    },
    {
        "qasm_async_intepreter_get_registers",
        qasm_async_intepreter_get_registers,
        METH_VARARGS,
        ""
    },
    {nullptr,nullptr,0,nullptr}
}; 




static struct PyModuleDef MiniQbtModuleMethods = {
    PyModuleDef_HEAD_INIT,
    "MiniQbt",
    "",
    -1,
    MiniQbtMethods,
    NULL,
    NULL,                /* m_reload */
    NULL,                /* m_traverse */
    clear_memory,                /* m_clear */
};


PyMODINIT_FUNC PyInit_MiniQbtNative(void){
    return PyModule_Create(&MiniQbtModuleMethods);
}
