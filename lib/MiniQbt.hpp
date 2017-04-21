#ifndef MINI_QBT_HPP
#define MINI_QBT_HPP

#include "core/HadamardGate.hpp"
#include "core/Measure.hpp"
#include "core/Exceptions.hpp"
#include "core/ControlledNotGate.hpp"
#include "core/PauliGates.hpp"
#include <random>
#include <bitset>
#include <memory>

namespace MiniQbt{
    constexpr char VERSION[] = "0.1.0";
    constexpr char NAME[] = "MiniQBT";



    template<size_t registerSize, bool strictMode = true>
    struct QuantumEmulator{
        Core::QuantumState<registerSize> generateRegister() const{
            static_assert(registerSize > 0 , "You need to have a register of at least on qubit...");
            return Core::QuantumState<registerSize>();
        }

        void hadamardGate(const size_t& bit, Core::QuantumState<registerSize>& state) const{
            Core::hadamardGate<registerSize, strictMode>(bit,state);
        }

        void controlledNot(const size_t& control, const size_t& target, Core::QuantumState<registerSize>& state) const{
            Core::cnotGate<registerSize>(control,target,state);
        }

        std::bitset<registerSize> measure(Core::QuantumState<registerSize>& state, std::default_random_engine& generator) const{
            return Core::measure<registerSize, strictMode>(state, generator);
        }

        void pauliX(const size_t& bit_index, Core::QuantumState<registerSize>& state) const{
            Core::pauliX<registerSize>(bit_index, state);
        }

        void pauliY(const size_t& bit_index, Core::QuantumState<registerSize>& state) const{
            Core::pauliY<registerSize>(bit_index, state);
        }

        void pauliZ(const size_t& bit_index, Core::QuantumState<registerSize>& state) const{
            Core::pauliZ<registerSize>(bit_index, state);
        }

        void phaseS(const size_t& bit_index, Core::QuantumState<registerSize>& state) const{
            throw QuantumException("Not yet implemented :(");
        }
    };

    /**
    *   Some predefined quantum emulators with the amount of qubits
    */
    typedef QuantumEmulator<1, true> Quantum1;
    typedef QuantumEmulator<2, true> Quantum2;
    typedef QuantumEmulator<3, true> Quantum3;
    typedef QuantumEmulator<4, true> Quantum4;
    typedef QuantumEmulator<5, true> Quantum5;
    typedef QuantumEmulator<6, true> Quantum6;
    typedef QuantumEmulator<7, true> Quantum7;
    typedef QuantumEmulator<8, true> Quantum8;
    typedef QuantumEmulator<9, true> Quantum9;
    typedef QuantumEmulator<10,true> Quantum10;
    typedef QuantumEmulator<11,true> Quantum11;
    typedef QuantumEmulator<12,true> Quantum12;
    typedef QuantumEmulator<13,true> Quantum13;
    typedef QuantumEmulator<14,true> Quantum14;
    typedef QuantumEmulator<15,true> Quantum15;
    typedef QuantumEmulator<16,true> Quantum16;
    typedef QuantumEmulator<17,true> Quantum17;
    typedef QuantumEmulator<18,true> Quantum18;
    typedef QuantumEmulator<19,true> Quantum19;
    typedef QuantumEmulator<20,true> Quantum20;
}




#endif