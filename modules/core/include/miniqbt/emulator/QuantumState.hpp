#ifndef QUANTUM_STATE_HPP
#define QUANTUM_STATE_HPP

#include "tools/Utils.hpp"
#include <string>
#include <complex>
#include <Eigen/Dense>
#include <memory>
#include <ostream>
#include "Exceptions.hpp"
#include <cmath>



namespace MiniQbt{
    namespace Core{

        template<int registerSize>
        class QuantumState {
            private:
            bool invalid = false;
            Eigen::Matrix<std::complex<double>, Eigen::Dynamic, 1>  data;
            public:
            QuantumState(){
                this->data = Eigen::Matrix<std::complex<double>, Eigen::Dynamic, 1>::Zero(std::pow(2,registerSize));
                data(0,0) = 1;
                for(int i = 1; i < this->data.rows(); i++){
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
            int getAmountOfPossibilities() const{
                return this->data.rows();
            }
            QuantumState& operator=(const Eigen::Matrix<std::complex<double>, Eigen::Dynamic, 1>& lh){
                this->data = lh;
                return *this;
            }

            QuantumState& operator*=(const Eigen::Matrix<std::complex<double>, Eigen::Dynamic, 1>& lh){
                this->data *= lh;
                return *this;
            }
            friend std::ostream& operator<<(std::ostream& os, const QuantumState& state){
                os << state.getState();
                return os;
            }

        };
    }
}

#endif