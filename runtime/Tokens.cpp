#include "Tokens.hpp"
#include "TokenVisitor.hpp"

void QuantumRegister::accept(TokenVisitor& visitor) {
    visitor.visit(*this);
}

void HadamardGate::accept(TokenVisitor& visitor) {
    visitor.visit(*this);
}

void PauliX::accept(TokenVisitor& visitor) {
    visitor.visit(*this);
}

void Measure::accept(TokenVisitor& visitor)  {
    visitor.visit(*this);
}