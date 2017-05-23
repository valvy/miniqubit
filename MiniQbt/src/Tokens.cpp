#include "miniqbt/intepreter/Tokens.hpp"
#include "miniqbt/intepreter/TokenVisitor.hpp"
#include <regex>

using namespace MiniQbt::Core;



GateToken::GateToken(const std::string& data){
    std::regex parseToken("\\s*gate\\s*([a-z|A-Z|0-9]+)\\s*\\(?([^\\)]*)\\)?\\s*([^{]*)\\{([^}]*)\\}", std::regex::ECMAScript);
    std::smatch m;
    std::regex_match(data, m, parseToken);
    this->name = m[1];
    this->classicArguments = m[2];
    this->quantumArguments = m[3];
    this->instructions = m[4];
}


UnkownGateToken:: UnkownGateToken(const std::string& name, const std::string classicArguments, const std::string quantumArguments){
    this->name = name;
}

void UnkownGateToken::accept(TokenVisitor& visitor){

}

void QuantumRegisterToken::accept(TokenVisitor& visitor) {
    visitor.visit(*this);
}

void ClassicRegisterToken::accept(TokenVisitor& visitor) {
    visitor.visit(*this);
}

void AssemblyVersionToken::accept(TokenVisitor& visitor){
    //nothing yet
}

void IncludeToken::accept(TokenVisitor& visitor){

}


void GateToken::accept(TokenVisitor& visitor){
    visitor.visit(*this);
}

void HadamardGateToken::accept(TokenVisitor& visitor) {
    visitor.visit(*this);
}

void ErrorToken::accept(TokenVisitor& visitor){
    visitor.visit(*this);
}

void PauliYToken::accept(TokenVisitor& visitor) {
    visitor.visit(*this);
}

void PauliZToken::accept(TokenVisitor& visitor) {
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