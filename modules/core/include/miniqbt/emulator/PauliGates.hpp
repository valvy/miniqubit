#ifndef MINI_QBT_PAULI_GATES_HPP
#define MINI_QBT_PAULI_GATES_HPP

namespace MiniQbt{
    namespace Core{
        template<size_t registerSize>

        /**
        *   Applies the pauli Y gate to the specified quantum bit and quantum state.
        *   @param bit_index, the quantum bit you wish to apply the pauli gate on.
        *   @param state, the quantum state you wish to alter.
        */
        void pauliY(const size_t& bit_index, QuantumState<registerSize>& state){
            using namespace Tools;
            //Check if the input is correct
            assertInput(bit_index >= registerSize, "Bit index exceeds the registerSize");
            std::array<ChanceOrder<registerSize>, Tools::vectorLength<registerSize>::value> everything;
            for(size_t i = 0; i < state.getAmountOfPossibilities(); i++){
                ChanceOrder<registerSize> ord(i, state.getState()(i,0));
                //Check for every possibility and when the bit on bit index is zero alter it
                if(ord[bit_index] == 0){
                    ord.data = ord.data * std::complex<double>(0,-1);
                } else {
                    ord.data = std::complex<double>(0,1) * ord.data;
                }
                everything[i] = ord;
            }
            //MErge together
            Eigen::Matrix<std::complex<double>, Eigen::Dynamic, 1> res = Eigen::Matrix<std::complex<double>, Eigen::Dynamic, 1>::Zero(Tools::vectorLength<registerSize>::value, 1);
            for(const ChanceOrder<registerSize>& b : everything){
                res(b.originalPos,0) = b.data;
            }
            state = res;
        }

        template<size_t registerSize>
        void pauliZ(const size_t& bit_index, QuantumState<registerSize>& state){
            using namespace Tools;
            assertInput(bit_index >= registerSize, "Bit index exceeds the registerSize");
            std::array<ChanceOrder<registerSize>, Tools::vectorLength<registerSize>::value> everything;
            for(size_t i = 0; i < state.getAmountOfPossibilities(); i++){
                ChanceOrder<registerSize> ord(i, state.getState()(i,0));
                if(ord[bit_index] == 0){
                    ord.data =  -ord.data;
                }
                everything[i] = ord;
            }
            Eigen::Matrix<std::complex<double>, Eigen::Dynamic, 1> res = Eigen::Matrix<std::complex<double>, Eigen::Dynamic, 1>::Zero(Tools::vectorLength<registerSize>::value, 1);
            for(const ChanceOrder<registerSize>& b : everything){
                res(b.originalPos,0) = b.data;
            }
            state = res;

            
        }

        template<size_t registerSize>
        void pauliX(const size_t& bit_index, QuantumState<registerSize>& state){
            using namespace Tools;
            assertInput(bit_index >= registerSize, "Bit index exceeds the registerSize");
            std::array<ChanceOrder<registerSize>, Tools::vectorLength<registerSize>::value> everything;
            for(size_t i = 0; i < state.getAmountOfPossibilities(); i++){
                everything[i] = ChanceOrder<registerSize>(i, state.getState()(i,0));
            }
            for(size_t i = 0; i < everything.size(); i++){
                everything[i].bitflip( bit_index );
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