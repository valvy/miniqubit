#include "core/Tokens.hpp"
#include "core/TokenVisitor.hpp"

using namespace MiniQbt::Core;

void QuantumRegister::accept(TokenVisitor& visitor) {
    visitor.visit(*this);
}

void HadamardGate::accept(TokenVisitor& visitor) {
    visitor.visit(*this);
}

void ErrorToken::accept(TokenVisitor& visitor){
    visitor.visit(*this);
}

void PauliX::accept(TokenVisitor& visitor) {
    visitor.visit(*this);
}

void Measure::accept(TokenVisitor& visitor)  {
    visitor.visit(*this);
}

void CNot::accept(TokenVisitor& visitor){
    visitor.visit(*this);
}