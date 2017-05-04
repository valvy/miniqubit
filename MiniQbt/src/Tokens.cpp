#include "miniqbt/intepreter/Tokens.hpp"
#include "miniqbt/intepreter/TokenVisitor.hpp"

using namespace MiniQbt::Core;

void QuantumRegisterToken::accept(TokenVisitor& visitor) {
    visitor.visit(*this);
}

void ClassicRegisterToken::accept(TokenVisitor& visitor) {
    visitor.visit(*this);
}


void HadamardGateToken::accept(TokenVisitor& visitor) {
    visitor.visit(*this);
}

void ErrorToken::accept(TokenVisitor& visitor){
    visitor.visit(*this);
}

void PauliXToken::accept(TokenVisitor& visitor) {
    visitor.visit(*this);
}

void MeasureToken::accept(TokenVisitor& visitor)  {
    visitor.visit(*this);
}

void CNotToken::accept(TokenVisitor& visitor){
    visitor.visit(*this);
}