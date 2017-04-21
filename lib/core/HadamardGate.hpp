#ifndef MINI_QBT_HADAMARD_GATE_HPP
#define MINI_QBT_HADAMARD_GATE_HPP

#include "./tools/ChanceOrder.hpp"
#include "./tools/Utils.hpp"

namespace MiniQbt{
    namespace Core{
        constexpr double F = 0.7071067811865476;

        template<size_t registerSize, bool strictMode = true>
        void hadamardGate(const size_t& bit_index, QuantumState<registerSize>& state){
            using namespace Tools;
            assertInput(bit_index > registerSize - 1, "The control bit must be within range of the amount of qbits residing in this state..");
            if(strictMode){
                assertInput(!state.usable(), "This state has been entangled and can no longer be used seperatly");
            }
            std::vector<ChanceOrder<registerSize>> everything;
            for(size_t i = 0; i < state.getAmountOfPossibilities(); i++){
                everything.push_back(ChanceOrder<registerSize>(i, state.getState()(i,0)));
            }
            std::vector<ChanceOrder<registerSize>> copy = everything;
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
            state = mergeOrderProb<registerSize>(everything, std::vector<ChanceOrder<registerSize>>());
        }
    }
}
#endif