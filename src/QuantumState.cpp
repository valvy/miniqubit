#include "QuantumState.hpp"
#include <unsupported/Eigen/KroneckerProduct>
#include <cmath>
#include "Globals.hpp"
#include <iostream>


QuantumState::QuantumState(const QuantumData& state, bool allowInfinity){
    this->data = QuantumData(state);
    infinityCheck(allowInfinity);
 }


QuantumState::QuantumState(QuantumState& lh, QuantumState& rh, bool allowInfinity){
    rh.setInvalid();
    lh.setInvalid(); //the other states are now invalid.. since they are entangled with this state.
    this->data = Eigen::kroneckerProduct<QuantumData, QuantumData>(lh.getState(), rh.getState());
}

QuantumState::QuantumState(const QuantumData& lh, const QuantumData& rh, bool allowInfinity){
    this->data = Eigen::kroneckerProduct<QuantumData, QuantumData>(rh, lh);
    infinityCheck(allowInfinity);
 }

void QuantumState::setInvalid(){
    this->invalid = true;
}

void QuantumState::infinityCheck(const bool& allowInfinity){
    if(!allowInfinity){
        if(this->getAmountOfQBytes() > Globals::QUANTUM_INFINITY){
            throw QuantumInfinityException("More then 20 qubits will take a really long time...");
        }
         
    }
}

QuantumState::QuantumState(std::complex<double> lh, std::complex<double> rh, bool allowInfinity){
    this->data = QuantumData::Zero(2,1);
    this->data << lh , rh;
    infinityCheck(allowInfinity);
}

bool QuantumState::usable() const{
    return !this->invalid;
}

std::ostream& operator<<(std::ostream& os, const QuantumState& state){
    os << state.getState();
    return os;
}

QuantumData QuantumState::getState() const{
   return this->data;
}

QuantumState QuantumState::getZero(){
   return QuantumState(1.0,0.0);
   
}

QuantumState QuantumState::getOne(){
    return QuantumState(0.0,1.0);
}

void QuantumState::set(const QuantumData& data){
    this->data = data;
}

QuantumState& QuantumState::operator*=(const QuantumData& lh){
    this->data *= lh;
    return *this;
}

QuantumState& QuantumState::operator=(const QuantumData& lh){
    this->set(lh);

    return *this;
 }

size_t QuantumState::getAmountOfQBytes() const{
    return std::sqrt(this->data.size() + 1 );
}

size_t QuantumState::getAmountOfPossibilities() const{
    return this->data.rows();
}