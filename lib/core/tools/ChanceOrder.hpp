#ifndef MINI_QBT_CHANCE_ORDER_HPP
#define MINI_QBT_CHANCE_ORDER_HPP

#include<complex>
#include<ostream>
#include<bitset>

namespace MiniQbt{
    namespace Core{
        namespace Tools{      
            /**
            *   Small struct to easily disassemble and reassemble bit orders of the program.
            *   Might not be the best and fastest solution but it does get the job done.
            *   This will however allow me to make infinite big quantum computer :D
            */
            template<size_t amountOfBits>
            struct ChanceOrder{
                size_t originalPos;
                std::complex<double> data;
                //size_t amountOfBits;
                ChanceOrder(size_t originalPos, const std::complex<double>& data) : 
                originalPos(originalPos), data(data) {}
                friend std::ostream& operator<<(std::ostream& os, const ChanceOrder& state){
                    os << state.data << " : "<< std::bitset<amountOfBits>(state.originalPos);
                    return os;
                }
                size_t getAmountOfBits() const{
                    return amountOfBits;//Index start at zero...
                }
                /**
                *   Toggles the bit, Usefull for the CNOT Gate. 
                *   (Watch out if not done correctly assembling the bits will not reassemble)
                */
                void bitflip(const size_t bitChange){
                    std::bitset<amountOfBits> bit(originalPos);
                    const size_t trueBitPos = amountOfBits - bitChange - 1;
                    bit[trueBitPos] = !bit[trueBitPos];
                    
                    originalPos =  (int)bit.to_ulong();
                }

                const size_t operator[] ( int bit) const{
                    return std::bitset<amountOfBits>(originalPos)[amountOfBits - bit - 1];
                }

            };
        }
    }
}
#endif
