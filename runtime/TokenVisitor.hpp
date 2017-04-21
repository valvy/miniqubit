#ifndef MINI_QBT_TOKEN_VISITOR_HPP
#define MINI_QBT_TOKEN_VISITOR_HPP

#include "Tokens.hpp"
#include <MiniQbt.hpp>
#include "RegisterDelegate.hpp"


class TokenVisitor{
    private:
    bool registerDoesExist(const std::string& name) const;
    std::vector<AbstractDelegate*> registers;
    public:
    TokenVisitor();
    void visit(PauliX& pauliGate);
    void visit(HadamardGate& hadamard);
    void visit(Measure& measure);
    void visit(QuantumRegister& registe);
    void visit(CNot& cnot);

};

#endif