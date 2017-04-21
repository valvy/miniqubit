#ifndef MINI_QBT_TOKEN_VISITOR_HPP
#define MINI_QBT_TOKEN_VISITOR_HPP

#include "Tokens.hpp"
#include <MiniQbt.hpp>

class TokenVisitor{
    private:
    MiniQbt::Quantum5 emulator;
    MiniQbt::Core::QuantumState<5> quantumRegister;
    public:
    TokenVisitor();
    void visit(PauliX& pauliGate);
    void visit(HadamardGate& hadamard);
    void visit(Measure& measure);
    void visit(QuantumRegister& registe);

};

#endif