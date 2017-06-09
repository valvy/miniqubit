#ifndef MINI_QBT_HADAMARD_GATE_HPP
#define MINI_QBT_HADAMARD_GATE_HPP

#include "./tools/ChanceOrder.hpp"
#include "./tools/Utils.hpp"

namespace MiniQbt{
    namespace Core{


        /**
        *   Applies the hadamard gate (and thus place the state in superposition) on the specified quantumstate.
        *   @author Heiko van der Heijden
        *
        *   See the quantum state as a array wherein the index corresponds to the binary resperentation.
        *   Such as (register size 2) [0 == 00, 1 == 01, 2 == 10, 3 == 11]. And we want to apply the hadamard on bit zero
        *   The hadamard stores temporarily the order of the quantum state, and searches for each bit the twin bit (the bit that only differs in the control bit this is always two bits)
        *   It multiplies the bit with the 1 over squareroot(2) and increments/substracts it with the multiplication of F with the targetbit depending on if it's a 1 or 0.
        *   
        *   @param registerSize,        the size of the register
        *   @param strictMode,          Allows collapsed registers
        *   @param bit_index,           The bit you want to apply the hadamard gate
        *   @param state,               The state containing all the information
        *   @throws QuantumException    When the program is in strictmode and is already collapsed, also when the controlbit is invalid
        */
        template<int registerSize, bool strictMode = true>
        void hadamardGate(const int& bit_index, QuantumState<registerSize>& state){
            using namespace Tools;
            assertInput(bit_index > registerSize - 1, "The control bit must be within range of the amount of qbits residing in this state..");
            if(strictMode){
                assertInput(!state.usable(), "This state has been entangled and can no longer be used seperatly");
            }
            /**
            *   this is 1 divided by square root of 2
            */
            constexpr double F = 0.7071067811865476;
            std::array<ChanceOrder<registerSize>, Tools::vectorLength<registerSize>::value> everything;
            for(int i = 0; i < state.getAmountOfPossibilities(); i++){
                everything[i] = ChanceOrder<registerSize>(i, state.getState()(i,0));
            }
            std::array<ChanceOrder<registerSize>, Tools::vectorLength<registerSize>::value> copy = everything;
            for(size_t i = 0; i < everything.size(); i++ ){
                for(size_t j = 0; j < everything.size(); j++){
                    if(i == j){
                        continue;
                    } else {
                            if(oppositeBitset(copy[i], copy[j], bit_index)){            
                                if(copy[i][bit_index] == 0){
                                    everything[i].data = F * copy[i].data + F * copy[j].data;
                                } else {
                                    everything[i].data = F * copy[j].data - F * copy[i].data;
                                }
                            }
                    }

                }
            }
            Eigen::Matrix<std::complex<double>, Eigen::Dynamic, 1> res = Eigen::Matrix<std::complex<double>, Eigen::Dynamic, 1>::Zero(Tools::vectorLength<registerSize>::value, 1);
            for(const ChanceOrder<registerSize>& b : everything){
                res(b.originalPos,0) = b.data;
            }
    
            state = res;
        }
    }
}
#endif