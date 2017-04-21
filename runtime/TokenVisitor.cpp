#include "TokenVisitor.hpp"
#include <iostream>

TokenVisitor::TokenVisitor(){

}

void TokenVisitor::visit(PauliX& pauliGate){
    emulator.pauliX(pauliGate.getSize(),quantumRegister);
}

void TokenVisitor::visit(HadamardGate& hadamard){
    emulator.hadamardGate(hadamard.getSize(),quantumRegister);
}

void TokenVisitor::visit(Measure& measure){
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::bitset<5> result = emulator.measure(quantumRegister, generator);
    std::cout << result << "\n";
}

void TokenVisitor::visit(QuantumRegister& registe){
    quantumRegister =  emulator.generateRegister();
}