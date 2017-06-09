#ifndef MINI_QBT_MEASURE_HPP
#define MINI_QBT_MEASURE_HPP

#include "./Exceptions.hpp"
#include "./QuantumState.hpp"
#include <random>
#include <complex>

namespace MiniQbt{
    namespace Core{

        /**
        *   Measures a quantumstate and returns the classic bitset.
        *   @author Heiko van der Heijden
        *
        *   See the quantum state as a array wherein the index corresponds to the binary resperentation.
        *   Such as (register size 2) [0 == 00, 1 == 01, 2 == 10, 3 == 11]. When we want to measure the register we need to take a random number between 0 and 1.
        *   The quantumstate has for each index a specific value for example |0>. [chance 1.0 index 0 bitvalue 0, chance 0.0 index 1 bitvalue 1].
        *   We take the norm of each index and checks if it's more then the random number provided if so then the bitvalue of that specific index is the answer.
        *   
        *   @param registerSize,        the size of the quantumregister
        *   @param strictmode,          Throw a exception when the register is already measured
        *   @param state,               The state you wish to measure
        *   @param generator,           The generator deciding the random number
        *   @throws QuantumException,   When the state is already collapsed in strictmode or when the state was invalid
        */
        template<int registerSize, bool strictMode = true>
        std::bitset<registerSize> measure (QuantumState<registerSize>& state, std::default_random_engine& generator){
            if(strictMode){
                if(!state.usable()){
                    throw QuantumException("State has already been collapsed.. ");
                }
            }
            state.setInvalid();
            const auto s = state.getState();
            std::uniform_real_distribution<double> distribution(0.0,1.0);
            const double rand = distribution(generator);//Getting a random double between 0.0 and 
            int collapsedResult = 0;
            double sum = 0.0;
            for(int i = 0; i < s.rows(); i++){
                    collapsedResult++;
                    double norm = std::norm(s(i,0));
                    sum += norm;
                    if(rand <= sum){
                        return std::bitset<registerSize> (collapsedResult - 1);
                    }
            }
            throw QuantumException("Could not collapse state!");
        }
    }
}

#endif