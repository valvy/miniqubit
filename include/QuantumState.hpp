#ifndef QUANTUM_STATE_HPP
#define QUANTUM_STATE_HPP

#include <string>
#include <complex>
#include <Eigen/Dense>
#include <memory>
#include <ostream>
#include "Exceptions.hpp"
typedef Eigen::Matrix<std::complex<double>, Eigen::Dynamic, 1> QuantumData;

class QuantumState{
    private:
    void infinityCheck(const bool& allow);
    bool invalid = false;
    QuantumData data;
    public:
    QuantumState(const QuantumData& state, bool allowInfinity = false);
    QuantumState(QuantumState& lh, QuantumState& rh, bool allowInfinity = false);
    QuantumState(const QuantumData& lh, const QuantumData& rh, bool allowInfinity = false);
    QuantumState(std::complex<double> lh, std::complex<double> rh, bool allowInfinity = false);
    void setInvalid();
    bool usable() const;
    static QuantumState getZero();
    static QuantumState getOne();
    QuantumData getState() const;
    void set(const QuantumData& data);
    size_t getAmountOfQBytes() const;
    size_t getAmountOfPossibilities() const;
    QuantumState& operator=(const QuantumData& lh);
    QuantumState& operator*=(const QuantumData& lh);
    friend std::ostream& operator<<(std::ostream& os, const QuantumState& state); 

};


#endif