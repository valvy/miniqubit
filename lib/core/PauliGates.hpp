#ifndef MINI_QBT_PAULI_GATES_HPP
#define MINI_QBT_PAULI_GATES_HPP

namespace MiniQbt{
  namespace Core{
      template<size_t registerSize>
      void pauliY(const size_t& bit_index, QuantumState<registerSize>& state){
          using namespace Tools;
          std::vector<ChanceOrder<registerSize>> everything;
          for(size_t i = 0; i < state.getAmountOfPossibilities(); i++){
              ChanceOrder<registerSize> ord(i, state.getState()(i,0));
              if(ord[bit_index] == 0){
                  ord.data = ord.data * std::complex<double>(0,-1);
              }
              everything.push_back(ord);
          }
          state = mergeOrderProb<registerSize>(everything, std::vector<ChanceOrder<registerSize>>());
      }

      template<size_t registerSize>
      void pauliZ(const size_t& bit_index, QuantumState<registerSize>& state){
           using namespace Tools;
          std::vector<ChanceOrder<registerSize>> everything;
          for(size_t i = 0; i < state.getAmountOfPossibilities(); i++){
              ChanceOrder<registerSize> ord(i, state.getState()(i,0));
              if(ord[bit_index] == 0){
                  ord.data =  -ord.data;
              }
              everything.push_back(ord);
          }
          state = mergeOrderProb<registerSize>(everything, std::vector<ChanceOrder<registerSize>>());

          
      }

      template<size_t registerSize>
      void pauliX(const size_t& bit_index, QuantumState<registerSize>& state){
           using namespace Tools;
          std::vector<ChanceOrder<registerSize>> everything;
          for(size_t i = 0; i < state.getAmountOfPossibilities(); i++){
              everything.push_back(ChanceOrder<registerSize>(i, state.getState()(i,0)));
          }
          for(size_t i = 0; i < everything.size(); i++){
              everything[i].bitflip( bit_index );
          }
          state = mergeOrderProb<registerSize>(everything, std::vector<ChanceOrder<registerSize>>());
      }
  }
}

#endif