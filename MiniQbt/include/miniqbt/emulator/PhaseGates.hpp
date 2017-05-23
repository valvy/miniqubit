#ifndef MINI_QBT_PHASE_GATES_HPP
#define MINI_QBT_PHASE_GATES_HPP

#include <iostream>
namespace MiniQbt{
    namespace Core{

        template<size_t registerSize>
        void phaseS(const size_t& bit_index, QuantumState<registerSize>& state){
            using namespace Tools;
            assertInput(bit_index >= registerSize, "Bit index exceeds the registerSize");
            std::array<ChanceOrder<registerSize>, Tools::vectorLength<registerSize>::value> everything;
            std::complex<double> imag(0,1);
            for(size_t i = 0; i < state.getAmountOfPossibilities(); i++){
                ChanceOrder<registerSize> ord(i, state.getState()(i,0));
                if(ord[bit_index] == 1){
                    ord.data = imag * ord.data;
                } 
                
                everything[ord.originalPos] = ord;
            }
            
            Eigen::Matrix<std::complex<double>, Eigen::Dynamic, 1> res = Eigen::Matrix<std::complex<double>, Eigen::Dynamic, 1>::Zero(Tools::vectorLength<registerSize>::value, 1);
            for(const ChanceOrder<registerSize>& b : everything){
                res(b.originalPos,0) = b.data;
            }
            state = res;

        }


        template<size_t registerSize>
        void phaseSDG(const size_t& bit_index, QuantumState<registerSize>& state){
            using namespace Tools;
            assertInput(bit_index >= registerSize, "Bit index exceeds the registerSize");
            std::array<ChanceOrder<registerSize>, Tools::vectorLength<registerSize>::value> everything;
            std::complex<double> imag(0,1);
            for(size_t i = 0; i < state.getAmountOfPossibilities(); i++){
                ChanceOrder<registerSize> ord(i, state.getState()(i,0));
                if(ord[bit_index] == 1){
                    ord.data = -imag * ord.data;
                } 
                
                everything[ord.originalPos] = ord;
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