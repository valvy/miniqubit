#ifndef MINI_QBT_PHASE_GATES_HPP
#define MINI_QBT_PHASE_GATES_HPP

#define _USE_MATH_DEFINES // for C++  
#include <cmath>  
namespace MiniQbt{
    namespace Core{

        template<int registerSize>
        void phaseS(const int& bit_index, QuantumState<registerSize>& state, bool transpose = false){
            using namespace Tools;
			
            assertInput(bit_index >= registerSize, "Bit index exceeds the registerSize");
            std::array<ChanceOrder<registerSize>, Tools::vectorLength<registerSize>::value> everything;
            const std::complex<double> imag(0,(transpose)? -1 : 1);
            for(int i = 0; i < state.getAmountOfPossibilities(); i++){
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

        template<int registerSize>
        void phaseT(const int& bit_index, QuantumState<registerSize>& state, bool transpose = false){
            using namespace Tools;
            assertInput(bit_index >= registerSize, "Bit index exceeds the registerSize");
			constexpr double PI = 3.141592653589793238462643383279502884197;
			constexpr double E = 2.7182818284590452353602874713526624977572;
            std::array<ChanceOrder<registerSize>, Tools::vectorLength<registerSize>::value> everything;
            const std::complex<double> imag(0,(transpose)? -1 : 1);
            const std::complex<double> multi = std::pow(E, imag * PI / 4.0);

            for(int i = 0; i < state.getAmountOfPossibilities(); i++){
                ChanceOrder<registerSize> ord(i, state.getState()(i,0));
                if(ord[bit_index] == 1){
                    ord.data = multi * ord.data;
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