#ifndef GATES_HPP
#define GATES_HPP
#include <bitset>

#include "QuantumState.hpp"
#include "Exceptions.hpp"
#include <random>
typedef Eigen::Matrix<std::complex<double>, Eigen::Dynamic, Eigen::Dynamic> quantumGate;

void cnotGate(const size_t& control,const size_t& target, QuantumState& state);

/**
*   Applies a hadamard gate on the specified bit and state.
*/
void hadamardGate(const size_t& bit_index, QuantumState& state);

void phaseS(const size_t& bit_index, QuantumState& state);

void phaseSdg(const size_t& bit_index, QuantumState& state);

void pauliZ(const size_t& bit_index, QuantumState& state);

void pauliY(const size_t& bit_index, QuantumState& state);

void pauliX(const size_t& bit_index, QuantumState& state);

int collapse(const QuantumState& state, std::default_random_engine& dev);

template<size_t amountOfBits = 5>
std::bitset<amountOfBits> measure(const QuantumState&  state,std::default_random_engine& dev){
    //std::string decimal =  std::bitset<amountOfBits>(collapse(state,dev) - 1).to_string();
  //  std::reverse(decimal.begin(), decimal.end());
    return std::bitset<amountOfBits> ((collapse(state,dev) - 1));
}

#endif