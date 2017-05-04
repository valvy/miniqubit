#include "core/ClassicRegister.hpp"
#include "core/RegisterComposite.hpp"
#include <iostream>
using namespace MiniQbt::Core;

std::string ClassicRegister::getName() const{
    return name;
}

void ClassicRegister::setSize(const size_t& size){
    this->size = size;
    this->data.clear();
}

Bit ClassicRegister::operator[] (int position) const {
    for(const Bit& bit : data){
        if(bit.bitPos == position){
            return bit;
        }
    }
    if(position < size){
        return Bit(position,0,"");
    }
    throw InvalidInputException("Invalid position");
}

bool ClassicRegister::linkRegister(size_t bitPos, size_t quantumPos, const std::string& link, std::string& errorMsg){
    errorMsg = "";
    for(const Bit& bit : data){
        if(bit.bitPos == bitPos && bit.link == link){
            errorMsg = "Bit already defined..";
            return false;
        }
    }
    data.push_back(Bit(bitPos, quantumPos, link));
    return true;
}