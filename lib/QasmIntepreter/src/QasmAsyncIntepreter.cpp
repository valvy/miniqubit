#include "QasmAsyncIntepreter.hpp"
#include <iostream>
#include "core/TokenParser.hpp"
using namespace MiniQbt;

QasmAsyncIntepreter::QasmAsyncIntepreter(){
   
}

void QasmAsyncIntepreter::intepret(const std::string& line){
    if(line.length() == 0){
        return;
    }

    std::shared_ptr<Core::Token> res = Core::parseToken(line);
    if(res == nullptr){
        
    } else {
        res->accept(visitor);
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