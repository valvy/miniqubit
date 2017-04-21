#ifndef MINI_QBT_UTILS_HPP
#define MINI_QBT_UTILS_HPP

#include <vector>
#include "../QuantumState.hpp"
#include "ChanceOrder.hpp"

namespace MiniQbt{
    namespace Core{
        namespace Tools{


      
            /**
            *   Orders the bytes of a state. 
            *   When the first bit is static on two bit state: [[00,01],[10,11]].
            *   When the second bit is static on two bit state: [[00,10],[01,11]].
            *   when the first bit is static on three bit state: [[000,001,010,011],[100,101,110,111]].
            *   It will return always two vectors with the order
            */
            template<size_t registerSize>
            std::vector<std::vector<ChanceOrder<registerSize>>> orderByBit(const size_t bit_index, const QuantumState<registerSize>& state){
                
                assertInput(bit_index > registerSize - 1, "The control bit must be within range of the amount of qbits residing in this state..");
                std::vector<std::vector<ChanceOrder<registerSize>>> result;
                const Eigen::Matrix<std::complex<double>, Eigen::Dynamic, 1> d = state.getState();
                //Define the pattern.. 
                size_t divide = state.getAmountOfPossibilities();
                for(size_t i = bit_index + 1; i > 0; i--){
                    divide /= 2;
                }

                std::vector<ChanceOrder<registerSize>> lh;
                std::vector<ChanceOrder<registerSize>> rh;

                for(size_t i = 0; i < d.rows() ; i += divide * 2){
                    for(size_t j = i ; j < (divide + i); j++){
                        lh.push_back(ChanceOrder<registerSize>(j, d(j,0)));
                    }
                    for(size_t j = i + divide; j < ((divide * 2) + i); j++){
                        rh.push_back(ChanceOrder<registerSize>(j,d(j,0)));
                    }
                }
                
                result.push_back(lh);
                result.push_back(rh);
                return result;

            }

            /**
            *   Combines two vectors of merged data into one state.
            *   Required after an orderbit operation.
            */
            template<size_t bitSize>
            QuantumState<bitSize> mergeOrderProb(const std::vector<ChanceOrder<bitSize>>& lh, const std::vector<ChanceOrder<bitSize>>& rh){
            
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
                for(size_t i = 0; i < lh.getAmountOfBits(); i++){
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