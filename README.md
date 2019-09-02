# Miniqbt, a runtime for the IBM Quantum experience
[![Build Status](https://travis-ci.org/valvy/miniqubit.svg?branch=master)](https://travis-ci.org/valvy/miniqubit) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## Introduction
IBM research  [released](https://www.research.ibm.com/ibm-q/) a quantum computer accessable for the cloud.
MiniQbt is a emulator for the IBM quantum experience, with a generic amount of qubits and classical bits.
To contribute to MiniQbt please refer to [contributing](https://github.com/valvy/miniqubit/blob/master/CONTRIBUTING.md)

## installation
The best way of installation is to compile the program from source. For this you need to install the following dependancies. Please consult the individual tools for help.
1. Eigen3 (Compile from source at the website since some linux distros only have an old version in the repositories)
2. CMake
3. Python3 and the native development tools for python3
4. Git
5. Please use for Windows the Visual studio 2015 or later.

When done create a new build folder and let Cmake unpack everything there.


## Library usage
You can simply load in quantum source code like this.

```c++
#include <miniqbt/MiniQbt.hpp>
#include <iostream>
#include <vector>

int main(int argc, char** argv){
    using namespace MiniQbt;
    const char* src = 
    "OPENQASM 2.0;              \n"
    "include \"qelib1.inc\";    \n"
    "qreg q[1]; creg c[1];      \n"
    "h q[0];                    \n"
    "measure q[0] -> c[0];      \n";

    QasmAsyncInterpreter interpreter;
    interpreter.interpret(std::string(src));
    std::vector<bool> res = interpreter.readClassicRegister("c");
    while(interpreter.hasErrors()){
        std::cout << interpreter.getError() << "\n";
    }

    QuantumResult result = interpreter.readClassicResult("c");


    std::cout << "result of the algorithm: " << result.dataToString();

    std::cout << "\n";
}
```
The library has a wrapper for python
```python
from PyMiniQbt import QasmAsyncInterpreter

source = "OPENQASM 2.0; include \"qelib1.inc\";  qreg q[1]; creg c[1]; h q[0]; measure q[0] -> c[0];"
interpreter = QasmAsyncInterpreter()
interpreter.interpret(source)
result = interpreter.readClassicResult("c")
while interpreter.hasErrors():
    print(interpreter.getError())
print("result of the algorithm: ")
print(result.dataToString())

```

The library has also a wrapper for Java
```java
import nl.hvanderheijden.miniqbt.Globals;
import nl.hvanderheijden.miniqbt.QasmAsyncInterpreter;

public class Main {
    public static void main(String[] args) {
        System.out.println(
                String.format("%s version %s",
                        Globals.getName(),
                        Globals.getVersion()
                )
        );
        QasmAsyncInterpreter interpreter = new QasmAsyncInterpreter();
        interpreter.interpret("qreg a[5];");
        interpreter.interpret("creg b[5];");
        interpreter.interpret("h a;");
        interpreter.interpret("measure a -> b;");
        while(interpreter.hasErrors()) {
            System.out.println(interpreter.getError());
        }
        for (String i : interpreter.getRegisters()) {
            QuantumResult result = interpreter.readClassicResult(i);
            System.out.println(result.dataToString());
        }
    }
}

```