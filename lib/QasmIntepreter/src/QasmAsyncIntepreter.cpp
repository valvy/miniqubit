#include "QasmAsyncIntepreter.hpp"
#include "core/TokenParser.hpp"
using namespace MiniQbt;

QasmAsyncIntepreter::QasmAsyncIntepreter(){
   
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

void QasmAsyncIntepreter::stop(){

}