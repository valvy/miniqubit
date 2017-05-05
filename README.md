# Miniqbt, a runtime for the IBM Quantum experience
## Introduction
IBM research  [released](https://www.research.ibm.com/ibm-q/) a quantum computer accessable for the cloud.
MiniQbt emulates the assembly language up to 20 qubits (the header can go up to infinite qubits). It's written in c++ 14
This is alpha software and not ready for production, I would like to receive feedback or suggestions!



## Runtime usage
You can execute quantum algorithms using the miniqbt binary. The cap is 20 although this takes quite a while. 
To read from a file just pass the name into the arguments.

The runtime also contains a REPL allowing you execute commands on the fly.
![alt tag](https://raw.github.com/valvy/miniqubit/master/media/miniqbtScreen.png)



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

        QasmAsyncIntepreter intepreter;
        intepreter.intepret(std::string(src));
        std::vector<bool> res = intepreter.readClassicRegister("c");
        while(intepreter.hasErrors()){
            std::cout << intepreter.getError() << "\n";
        }


        std::cout << "result of the algorithm: ";
        for(const bool& r : res){
            std::cout << r;
        }
        std::cout << "\n";
    }
```
Or you can handle the quantum instructions in c++ aswell.
```c++
    #include <miniqbt/MiniQbt.hpp>
    #include <iostream>

    int main(int argc, char** argv){
        using namespace MiniQbt;
        //5 = Create a quantum emulator of 5 qubits
        //false = Allow for remeasurement
        QuantumEmulator<5, false> quantumEmulator;
        //Generate a register of 5 qubits
        auto quantumRegister = quantumEmulator.generateRegister();
        //Apply the hadamard gate on the first qubit
        quantumEmulator.hadamardGate(0, quantumRegister);

        std::random_device rd;
        std::default_random_engine generator(rd());
        //measure with a random number        
        std::bitset<5> bitset = quantumEmulator.measure(ent, generator);
        std::cout << "Result of the quantum algorithm : " << bitset << "\n";
    }

```

## Licence
Everything is licensed under the MIT license. 
[License](LICENSE)


