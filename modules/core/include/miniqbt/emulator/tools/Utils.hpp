#ifndef MINI_QBT_UTILS_HPP
#define MINI_QBT_UTILS_HPP

//#include <vector>
#include <array>
#include "../QuantumState.hpp"
#include "ChanceOrder.hpp"

namespace MiniQbt{
    namespace Core{
        namespace Tools{

            /*
            *   On compile time power of 2 to registerSize
            */
            template<size_t registerSize> 
            struct vectorLength{ enum { value = 2 * vectorLength<registerSize-1>::value}; };
            template<> 
            struct vectorLength<0>{ enum { value = 1 }; };


            /**
            *   Orders the bytes of a state. 
            *   When the first bit is static on two bit state: [[00,01],[10,11]].
            *   When the second bit is static on two bit state: [[00,10],[01,11]].
            *   when the first bit is static on three bit state: [[000,001,010,011],[100,101,110,111]].
            *   It will return always two vectors with the order
            */
            template<size_t registerSize> 
            std::array<std::array<ChanceOrder<registerSize>, vectorLength<registerSize>::value / 2> ,2> 
            orderByBit(const size_t bit_index, const QuantumState<registerSize>& state){
                assertInput(bit_index > registerSize - 1, "The control bit must be within range of the amount of qbits residing in this state..");
                std::array<std::array<ChanceOrder<registerSize>, vectorLength<registerSize>::value / 2> ,2>  result;

                const Eigen::Matrix<std::complex<double>, Eigen::Dynamic, 1> d = state.getState();
                //Define the pattern.. 
                int divide = state.getAmountOfPossibilities();
                for(int i = bit_index + 1; i > 0; i--){
                    divide /= 2;
                }

                int lhIndex = 0;
                int rhIndex = 0;
                for(int i = 0; i < d.rows() ; i += divide * 2){
                    
                    for(int j = i ; j < (divide + i); j++){
                        result[0][lhIndex] = ChanceOrder<registerSize>(j, d(j,0));
                        lhIndex++;
                    }
                 
                    for(int j = i + divide; j < ((divide * 2) + i); j++){
                        result[1][rhIndex] = ChanceOrder<registerSize>(j, d(j,0));
                        rhIndex++;
                    }
                }

                return result;
            }

            template<size_t bitSize>
            QuantumState<bitSize> mergeOrderProb(
                const std::array<ChanceOrder<bitSize>, vectorLength<bitSize>::value / 2>& lh, 
                const std::array<ChanceOrder<bitSize>, vectorLength<bitSize>::value / 2>& rh){
            
                Eigen::Matrix<std::complex<double>, Eigen::Dynamic, 1> res = Eigen::Matrix<std::complex<double>, Eigen::Dynamic, 1>::Zero(lh.size() + rh.size(), 1);
                for(const ChanceOrder<bitSize>& b : lh){

                    res(b.originalPos,0) = b.data;
                }
                for(const ChanceOrder<bitSize>& b : rh){
                    res(b.originalPos,0) = b.data;
                }


                return QuantumState<bitSize>(res);
            }


            template<size_t bitSize>
            bool oppositeBitset(const ChanceOrder<bitSize>& lh, const ChanceOrder<bitSize>& rh, const size_t& targetBit){
                for(size_t i = 0; i < bitSize; i++){
                    if(i == targetBit){
                        if(lh[i] == rh[i]){
                            return false; //that bit needs to be opposite..
                        }
                    } else {
                        if(lh[i] != rh[i]){
                            return false; //nope not the same
                        }
                    }
                }    
                return true;
            }
        }
    }
}
#endif