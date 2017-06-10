#include "miniqbt/interpreter/QasmAsyncInterpreter.hpp"
#include "miniqbt/interpreter/TokenParser.hpp"

using namespace MiniQbt;

QasmAsyncInterpreter::QasmAsyncInterpreter(){
   
}

bool QasmAsyncInterpreter::doesRegisterExists(const std::string& registerName) const{
    return visitor.doesRegisterExists(registerName);
}

void QasmAsyncInterpreter::resetSuperPosition(const std::string& quantumRegister){
    visitor.resetSuperPosition(quantumRegister);
}

std::vector<std::string> QasmAsyncInterpreter::getQuantumRegisters() const{
    return visitor.getQuantumRegisters();
}

std::vector<std::string> QasmAsyncInterpreter::getRegisters() const{
    return visitor.getClassicRegisters();
}

std::vector<bool> QasmAsyncInterpreter::readClassicRegister(const std::string& registerName){
    return visitor.getClassicRegister(registerName);
}

void QasmAsyncInterpreter::interpret(const std::string& line){
    if(line.length() == 0){
        return;
    }
    std::vector<std::shared_ptr<Core::Token>> res = Core::parseExpressions(line);
    for(const auto& d : res){
        d->accept(visitor);
    }
}

bool QasmAsyncInterpreter::hasErrors() const{
    return visitor.hasErrors();
}

std::string QasmAsyncInterpreter::getError(){
    return visitor.getError();
}
