#ifndef MINI_QBT_CONTROLLED_NOT_GATE_HPP
#define MINI_QBT_CONTROLLED_NOT_GATE_HPP

#include "./tools/Utils.hpp"
#include "./QuantumState.hpp"

namespace MiniQbt{
    namespace Core{


        /**
        *   Applies a controlled not gate on a quantum state.
        *   @Author Heiko van der Heijden
        *   
        *   See the quantum state as a array wherein the index corresponds to the binary resperentation.
        *   Such as (register size 2) [0 == 00, 1 == 01, 2 == 10, 3 == 11]. When you want to flip bit 0 based on bit 1.
        *   It will just ignore the bits where the bit control bit is 0, thus it will create a new array [2,3].
        *   After that the bit that's the same with only the target bit different will be found (no matter the registersize this is always 2)
        *   And reverses the value of each of this values [0, 1,  3, 2] is the new order.
        *
        *   @param registerSize,        the size a quantum register.
        *   @param control,             the quantum bit you wish to use as control, this bit will remain the same.
        *   @param target,              the quantum bit you wish to use as target, this bit will be flipped if the control is 1.
        *   @param state,               the state that will be altered.
        *   @throws QuantumException,   when the an invalid bit is altered it will throw a quantum exception
        */
        template<size_t registerSize>
        void cnotGate(const size_t& control,const size_t& target, QuantumState<registerSize>& state){
            using namespace Tools;
            assertInput(control == target, "The control bit can't be the same as the target bit...");
            assertInput(target >= registerSize, "Target bit can't be bigger then the register.");
            assertInput(control >= registerSize, "Control bit can't be bigger then the register.");
            
            auto order = orderByBit<registerSize>(control, state);
            for(size_t i = 0; i < order[1].size(); i++){
                order[1][i].bitflip(target); 
            }
            
            
            state = mergeOrderProb<registerSize>(order[0], order[1]);
        }
    }
}

#endif