#include "Utils.hpp"
#include "Exceptions.hpp"
void printProbabilities(const QuantumState& state){
    int bit = 0;
    for(size_t i = 0; i < state.getAmountOfQBytes(); i++){
        
    }

   // for(size_t i = 0;  i < state.getState().rows(); i++){
   //     std::complex<double> data = state.getState()(i,0);
   // }
}

void assertInput(const bool as, std::string msg){
    if(as){
        throw InvalidInputException(msg);
    }
}

void assertInfinity(const bool as, std::string msg){
    if(as){
        throw QuantumInfinityException(msg);
    }
}