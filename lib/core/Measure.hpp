#ifndef MINI_QBT_MEASURE_HPP
#define MINI_QBT_MEASURE_HPP

#include "./Exceptions.hpp"
#include "./QuantumState.hpp"
#include <random>
#include <complex>

namespace MiniQbt{
    namespace Core{
        template<size_t registerSize>
        std::bitset<registerSize> measure (QuantumState<registerSize>& state, std::default_random_engine& generator){
            const auto s = state.getState();
            std::uniform_real_distribution<double> distribution(0.0,1.0);
            const double rand = distribution(generator);//Getting a random double between 0.0 and 
            int collapsedResult = 0;
            double sum = 0.0;
            for(size_t i = 0; i < s.rows(); i++){
                    collapsedResult++;
                    double norm = std::norm(s(i,0));
                    sum += norm;
                    if(rand <= sum){
                        return std::bitset<registerSize> (collapsedResult - 1);
                    }
            }
            throw QuantumException("Could not collapse state!");
        }
    }
}

#endif