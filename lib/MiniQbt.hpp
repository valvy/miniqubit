#ifndef MINI_QBT_HPP
#define MINI_QBT_HPP

#include "core/HadamardGate.hpp"
#include "core/Measure.hpp"
#include "core/Exceptions.hpp"
#include "core/ControlledNotGate.hpp"
#include "core/PauliGates.hpp"
#include <random>
#include <bitset>

namespace MiniQbt{
    constexpr char VERSION[] = "0.0.1";
    constexpr char NAME[] = "MiniQBT";

    template<size_t registerSize>
    struct QuantumEmulator{
        Core::QuantumState<registerSize> generateRegister() const{
            return Core::QuantumState<registerSize>();
        }

        void hadamardGate(const size_t& bit, Core::QuantumState<registerSize>& state) const{
            Core::hadamardGate<registerSize>(bit,state);
        }

        void controlledNot(const size_t& control, const size_t target, Core::QuantumState<registerSize>& state) const{
            Core::cnotGate<registerSize>(control,target,state);
        }

        std::bitset<registerSize> measure(Core::QuantumState<registerSize>& state, std::default_random_engine& generator) const{
            return Core::measure<registerSize>(state, generator);
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
    typedef QuantumEmulator<1> Quantum1;
    typedef QuantumEmulator<2> Quantum2;
    typedef QuantumEmulator<3> Quantum3;
    typedef QuantumEmulator<4> Quantum4;
    typedef QuantumEmulator<5> Quantum5;
    typedef QuantumEmulator<6> Quantum6;
    typedef QuantumEmulator<7> Quantum7;
    typedef QuantumEmulator<8> Quantum8;
    typedef QuantumEmulator<9> Quantum9;
    typedef QuantumEmulator<10> Quantum10;
    typedef QuantumEmulator<11> Quantum11;
    typedef QuantumEmulator<12> Quantum12;
    typedef QuantumEmulator<13> Quantum13;
    typedef QuantumEmulator<14> Quantum14;
    typedef QuantumEmulator<15> Quantum15;
    typedef QuantumEmulator<16> Quantum16;
    typedef QuantumEmulator<17> Quantum17;
    typedef QuantumEmulator<18> Quantum18;
    typedef QuantumEmulator<19> Quantum19;
    typedef QuantumEmulator<20> Quantum20;
}




#endif