#include "miniqbt/intepreter/QasmAsyncIntepreter.hpp"
#include "miniqbt/intepreter/TokenParser.hpp"

using namespace MiniQbt;

QasmAsyncIntepreter::QasmAsyncIntepreter(){
   
}

bool QasmAsyncIntepreter::doesRegisterExists(const std::string& registerName) const{
    return visitor.doesRegisterExists(registerName);
}

void QasmAsyncIntepreter::resetSuperPosition(const std::string& quantumRegister){
    visitor.resetSuperPosition(quantumRegister);
}

std::vector<std::string> QasmAsyncIntepreter::getQuantumRegisters() const{
    return visitor.getQuantumRegisters();
}

std::vector<std::string> QasmAsyncIntepreter::getRegisters() const{
    return visitor.getClassicRegisters();
}

std::vector<bool> QasmAsyncIntepreter::readClassicRegister(const std::string& registerName){
    return visitor.getClassicRegister(registerName);
}

void QasmAsyncIntepreter::intepret(const std::string& line){
    if(line.length() == 0){
        return;
    }
    std::vector<std::shared_ptr<Core::Token>> res = Core::parseExpressions(line);
    for(const auto& d : res){
        d->accept(visitor);
    }
}

bool QasmAsyncIntepreter::hasErrors() const{
    return visitor.hasErrors();
}

std::string QasmAsyncIntepreter::getError(){
    return visitor.getError();
}
