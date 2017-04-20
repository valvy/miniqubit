#ifndef QUANTUM_STATE_HPP
#define QUANTUM_STATE_HPP

#include <string>
#include <complex>
#include <Eigen/Dense>
#include <memory>
#include <ostream>
#include "Exceptions.hpp"
#include <unsupported/Eigen/KroneckerProduct>
#include <cmath>
//#include "Globals.hpp"
//template<size_t registerSize>

namespace MiniQbt{
    namespace Core{
        template<size_t registerSize>
        class QuantumState{
        // typedef Eigen::Matrix<std::complex<double>, registerSize, 1> QuantumData;
            private:
            bool invalid = false;
            Eigen::Matrix<std::complex<double>, Eigen::Dynamic, 1>  data;
            public:
            QuantumState(){
                this->data = Eigen::Matrix<std::complex<double>, Eigen::Dynamic, 1>::Zero(std::pow(2, registerSize));
                data(0,0) = 1;
                for(size_t i = 1; i < this->data.rows(); i++){
                    data(i,0) = 0;
                }
            }
            QuantumState(const Eigen::Matrix<std::complex<double>, Eigen::Dynamic, 1>& state){
                this->data = Eigen::Matrix<std::complex<double>, Eigen::Dynamic, 1>(state);
            }
            void setInvalid(){
                this->invalid = true;
            }

            bool usable() const{
                return !this->invalid;
            }
            Eigen::Matrix<std::complex<double>, Eigen::Dynamic, 1> getState() const{
                return this->data;
            }
            void set(const Eigen::Matrix<std::complex<double>, Eigen::Dynamic, 1>& data){
                this->data = data;
            }
            size_t getAmountOfQBytes() const{
                return std::log(this->data.size()) / std::log(2);
            }

            size_t getAmountOfPossibilities() const{
                return this->data.rows();
            }
            QuantumState& operator=(const Eigen::Matrix<std::complex<double>, Eigen::Dynamic, 1>& lh);
            QuantumState& operator*=(const Eigen::Matrix<std::complex<double>, Eigen::Dynamic, 1>& lh){
                this->data *= lh;
                return *this;
            }
            friend std::ostream& operator<<(std::ostream& os, const QuantumState& state); 

        };
    }
}

#endif