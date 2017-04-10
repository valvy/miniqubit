#include "Exceptions.hpp"

QuantumException::QuantumException(char const* msg){
    this->msg = std::string(msg);
    
}


QuantumException::QuantumException(const std::string& msg){
    this->msg = std::string(msg);
}

std::string QuantumException::getMessage() const{
    return this->msg;
}

std::ostream& operator<<(std::ostream& os, const QuantumException& state){
    os << state.msg;;
    return os;
}

