#ifndef MINI_QBT_CONTROLLED_NOT_GATE_HPP
#define MINI_QBT_CONTROLLED_NOT_GATE_HPP

#include "./tools/Utils.hpp"
#include "./QuantumState.hpp"

namespace MiniQbt{
    namespace Core{
        template<size_t registerSize>
        void cnotGate(const size_t& control,const size_t& target, QuantumState<registerSize>& state){
            using namespace Tools;
            assertInput(control == target, "The control bit can't be the same as the target bit...");
            std::vector<std::vector<ChanceOrder<registerSize>>>  order = orderByBit<registerSize>(control, state);
            for(size_t i = 0; i < order[1].size(); i++){
                order[1][i].bitflip(target); 
            }
            state = mergeOrderProb<registerSize>(order[0], order[1]);
        }
    }
}

#endif