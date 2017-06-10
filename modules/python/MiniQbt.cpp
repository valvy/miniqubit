#include <Python.h>
#include <miniqbt/MiniQbt.hpp>
#include <vector>
#include <utility> 
#include <string>
#include <iostream>
#include <algorithm>
constexpr char ASYNC_CONSTANT[] = "[MiniQbt Async reference]";
static std::vector<std::pair<int, MiniQbt::QasmAsyncInterpreter*>> asyncInterpreters;

static PyObject *MiniQbtNativeException;

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
*   Calls a specific interpreter.
*   
*/
static PyObject* qasm_async_interpret(PyObject* self, PyObject* args){
    int reference = 0;
    const char* src;
    const char* command;
    
    if(!PyArg_ParseTuple(args, "(si)s",&command, &reference, &src)){ 
        return nullptr;
    }
    bool found = false;
    for(auto& interpreters : asyncInterpreters){
        if(interpreters.first == reference){
            found = true;
            interpreters.second->interpret(std::string(src));
            break;
        }
    }
    if(!found){
        PyErr_SetString(MiniQbtNativeException, "Invalid reference");
        return nullptr;
    }

    return Py_BuildValue("");
}

static PyObject* qasm_async_interpreter_has_errors(PyObject* self, PyObject* args){
    int reference = 0;
    const char* command;
    std::string result ="";
    if(!PyArg_ParseTuple(args, "(si)",&command, &reference)){ 
        return nullptr;
    }
    for(auto& interpreters : asyncInterpreters){
        if(interpreters.first == reference){
            return Py_BuildValue("b", interpreters.second->hasErrors());
        }
    }
    PyErr_SetString(MiniQbtNativeException, "Invalid reference");
    return nullptr;
}

static PyObject* qasm_async_interpreter_get_registers(PyObject* self, PyObject* args){
    int reference = 0;
    const char* command;
    if(!PyArg_ParseTuple(args, "(si)",&command, &reference)){ 
        return nullptr;
    }
    for(auto& interpreters : asyncInterpreters){
        if(interpreters.first == reference){
            PyObject* result = PyList_New(0);
            for(const std::string& d : interpreters.second->getRegisters()){
                PyList_Append(result,Py_BuildValue("s",d.c_str()));
            }
            return result;
        }
    }
    PyErr_SetString(MiniQbtNativeException, "Invalid reference");
    return nullptr;
}

static PyObject* qasm_async_get_quantum_registers(PyObject* self, PyObject* args){
    int reference = 0;
    const char* command;
    if(!PyArg_ParseTuple(args, "(si)",&command, &reference)){ 
        return nullptr;
    }
    for(auto& interpreters : asyncInterpreters){
        if(interpreters.first == reference){
            PyObject* result = PyList_New(0);
            for(const std::string& d : interpreters.second->getQuantumRegisters()){
                PyList_Append(result,Py_BuildValue("s",d.c_str()));
            }
            return result;
        }
    }
    PyErr_SetString(MiniQbtNativeException, "Invalid reference");
    return nullptr;
}


static PyObject* qasm_async_interpreter_get_error(PyObject* self, PyObject* args){
    int reference = 0;
    const char* command;
    std::string result ="";
    if(!PyArg_ParseTuple(args, "(si)",&command, &reference)){ 
        return nullptr;
    }
    for(auto& interpreters : asyncInterpreters){
        if(interpreters.first == reference){
            return Py_BuildValue("s", interpreters.second->getError().c_str());
        }
    }
    PyErr_SetString(MiniQbtNativeException, "Invalid reference");
    return nullptr;
}

static PyObject* qasm_async_read_classic_register(PyObject* self, PyObject* args){
    int reference = 0;
    const char* name;
    const char* command;
    std::string result ="";
    if(!PyArg_ParseTuple(args, "(si)s",&command, &reference, &name)){ 
        return nullptr;
    }
    bool found = false;
    for(auto& interpreters : asyncInterpreters){
        if(interpreters.first == reference){
            found = true;
            std::vector<bool> d = interpreters.second->readClassicRegister(std::string(name));
            for(const bool& r : d){
                result += std::to_string(r);
            }
            break;
        }
    }
    if(found){
        return Py_BuildValue("s", result.c_str());
    }
    PyErr_SetString(MiniQbtNativeException, "Invalid reference");
    return nullptr;   
}



static PyObject* destroy_qasm_async_interpreter(PyObject* self, PyObject* args){
    int reference = 0;
    const char* command;
    
    if(!PyArg_ParseTuple(args, "(si)",&command, &reference)){ 
        return nullptr;
    }
    bool found = false;
    asyncInterpreters.erase(
        std::remove_if(asyncInterpreters.begin(), asyncInterpreters.end(), 
        [&found, &reference](std::pair<int, MiniQbt::QasmAsyncInterpreter*> x) { 
            if(x.first == reference){
                delete x.second;
                found = true;
                return true;
            }
            return false;
        }), asyncInterpreters.end()
    );
    if(found){
        return Py_BuildValue("");
    } else {
        PyErr_SetString(MiniQbtNativeException, "Invalid reference");
        return nullptr;
    }
    
}

static PyObject* qasm_async_interpreter_reset_super_position(PyObject* self, PyObject* args){
    int reference = 0;
    const char* name;
    const char* command;
    if(!PyArg_ParseTuple(args, "(si)s",&command, &reference, &name)){ 
        return nullptr;
    }
    bool found = false;
    for(auto& interpreters : asyncInterpreters){
        if(interpreters.first == reference){
            found = true;
            interpreters.second->resetSuperPosition(std::string(name));
            break;
        }
    }

    if(found){
        return Py_BuildValue("");
    } else {
        PyErr_SetString(MiniQbtNativeException, "Invalid reference");
        return nullptr;
    }
}

static PyObject* init_qasm_async_interpreter(PyObject* self, PyObject* args){
    int nr = getUniqueNumber();     
    asyncInterpreters.push_back(
        std::make_pair(
            nr,
            new MiniQbt::QasmAsyncInterpreter()
        )
    );

    return Py_BuildValue("si",ASYNC_CONSTANT, nr);
}

static void clear_memory(void* mem){
    for(auto& d : asyncInterpreters){
        delete d.second;
    }
    asyncInterpreters.clear();
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
        "init_qasm_async_interpreter",
        init_qasm_async_interpreter,
        METH_VARARGS,
        "Initializes the asynchronous interpreter"
    },
    {
        "qasm_async_interpreter_reset_super_position",
        qasm_async_interpreter_reset_super_position,
        METH_VARARGS,
        "Resets the quantum register to a quantum state. This is not possible on real quantum computers"
    },
    {
        "async_interpret",
        qasm_async_interpret,
        METH_VARARGS,
        ""
    },
    {
        "destroy_qasm_async_interpreter",
        destroy_qasm_async_interpreter,
        METH_VARARGS,
        ""
    },
    {
        "qasm_async_get_quantum_registers",
        qasm_async_get_quantum_registers,
        METH_VARARGS,
        "Gets all the quantum registers"
    },
    {
        "qasm_async_read_classic_register",
        qasm_async_read_classic_register,
        METH_VARARGS,
        ""
        
    },
    {
        "qasm_async_interpreter_has_errors",
        qasm_async_interpreter_has_errors,
        METH_VARARGS,
        "Native call to check if the specified quantum computer has an error."
    },
    {
        "qasm_async_interpreter_get_error",
        qasm_async_interpreter_get_error,
        METH_VARARGS,
        "Native call to get an error as string from the specified quantum computer.\n When the quantum computer doesn't exists it will raise an exception."
    },
    {
        "qasm_async_interpreter_get_registers",
        qasm_async_interpreter_get_registers,
        METH_VARARGS,
        " Native call to get all the registers from the specified quantum computer. \n When the quantum computer doesn't exists it will raise an exception."
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
    MiniQbtNativeException = PyErr_NewException("MiniQbt.error", NULL, NULL);
    PyObject *module = PyModule_Create(&MiniQbtModuleMethods);
    Py_INCREF(MiniQbtNativeException);
    PyModule_AddObject(module, "error",MiniQbtNativeException );
    return module;
}
