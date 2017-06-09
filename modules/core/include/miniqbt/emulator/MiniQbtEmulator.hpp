#ifndef MINI_QBT_EMULATOR_HPP
#define MINI_QBT_EMULATOR_HPP

#include "HadamardGate.hpp"
#include "Measure.hpp"
#include "Exceptions.hpp"
#include "ControlledNotGate.hpp"
#include "PauliGates.hpp"
#include "PhaseGates.hpp"
#include <random>
#include <bitset>

namespace MiniQbt{

    /**
    *   Facade class containing all the quantum gates and allows for generating quantum registers.
    *   @author Heiko van der Heijden.
    */
    template<int registerSize, bool strictMode = true>
    struct QuantumEmulator{
        /**
        *   Generates a quantum register to be used on this quantum emulator.
        */
        Core::QuantumState<registerSize> generateRegister() const{
            static_assert(registerSize > 0 , "You need to have a register of at least on qubit...");
            return Core::QuantumState<registerSize>();
        }

        /**
        *   Applies the hadamard gate to the specified quantum register and the specified quantum bit.
        *   @param bit, the bit index you wish to apply the quantum gate on.
        *   @param state, the quantum register you wish to apply the hadamard gate on.
        */
        void hadamardGate(const int& bit, Core::QuantumState<registerSize>& state) const{
            Core::hadamardGate<registerSize, strictMode>(bit,state);
        }

        /**
        *   Applies the controlled not gate on the specified states and bits.
        *   @param control, the control bit you wish to check.
        *   @param target, the target bit you wish to flip based on the control.
        *   @param state, the state you wish to alter.
        */
        void controlledNot(const int& control, const int& target, Core::QuantumState<registerSize>& state) const{
            Core::cnotGate<registerSize>(control,target,state);
        }

        /**
        *   Measures the result of a quantum state.
        *   @param state, the state you wish to measure.
        *   @param generator, the random number generator.
        */
        std::bitset<registerSize> measure(Core::QuantumState<registerSize>& state, std::default_random_engine& generator) const{
            return Core::measure<registerSize, strictMode>(state, generator);
        }

        /**
        *   Applies the pauli X (bit flip) gate to the specified qubit and state.
        *   @param bit_index, the qubit you wish to flip.
        *   @param state, the register you wish to alter.
        */
        void pauliX(const int& bit_index, Core::QuantumState<registerSize>& state) const{
            Core::pauliX<registerSize>(bit_index, state);
        }

       /**
        *   Applies the pauli y  gate to the specified qubit and state.
        *   @param bit_index, the qubit you wish to alter.
        *   @param state, the register you wish to alter.
        */
        void pauliY(const int& bit_index, Core::QuantumState<registerSize>& state) const{
            Core::pauliY<registerSize>(bit_index, state);
        }

       /**
        *   Applies the pauli z  gate to the specified qubit and state.
        *   @param bit_index, the qubit you wish to alter.
        *   @param state, the register you wish to alter.
        */
        void pauliZ(const int& bit_index, Core::QuantumState<registerSize>& state) const{
            Core::pauliZ<registerSize>(bit_index, state);
        }

        /**
        *   Applies the phase s  gate to the specified qubit and state.
        *   @param bit_index, the qubit you wish to alter.
        *   @param state, the register you wish to alter.
        */
        void phaseS(const int& bit_index, Core::QuantumState<registerSize>& state) const{
            Core::phaseS<registerSize>(bit_index, state, false);
        }

        /**
        *   Applies the phase s dagger  gate to the specified qubit and state.
        *   @param bit_index, the qubit you wish to alter.
        *   @param state, the register you wish to alter.
        */
        void phaseSDG(const int& bit_index, Core::QuantumState<registerSize>& state) const{
            Core::phaseS<registerSize>(bit_index, state, true);
        }

        /**
        *   Applies the phase Transpose  gate to the specified qubit and state.
        *   @param bit_index, the qubit you wish to alter.
        *   @param state, the register you wish to alter.
        */
        void phaseT(const int& bit_index, Core::QuantumState<registerSize>& state) const{
            Core::phaseT<registerSize>(bit_index, state, false);
        }


        /**
        *   Applies the phase Transpose Dagger  gate to the specified qubit and state.
        *   @param bit_index, the qubit you wish to alter.
        *   @param state, the register you wish to alter.
        */
        void phaseTDG(const int& bit_index, Core::QuantumState<registerSize>& state) const{
            Core::phaseT<registerSize>(bit_index, state, true);
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