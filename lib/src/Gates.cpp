#include "Gates.hpp"
#include "Globals.hpp"
#include <vector>
#include <iostream>
#include <unsupported/Eigen/KroneckerProduct>
#include "Utils.hpp"
#include <functional>


/**
*   Small struct to easily disassemble and reassemble bit orders of the program.
*   Might not be the best and fastest solution but it does get the job done.
*   This will however allow me to make infinite big quantum computer :D
*/
struct ChanceOrder{
    size_t originalPos;
    std::complex<double> data;
    size_t amountOfBits;
    ChanceOrder(size_t originalPos, const std::complex<double>& data, size_t amountOfBits) : 
    originalPos(originalPos), data(data), amountOfBits(amountOfBits) {}
    friend std::ostream& operator<<(std::ostream& os, const ChanceOrder& state){
        os << state.data << " : "<< std::bitset<Globals::QUANTUM_INFINITY>(state.originalPos);
        return os;
    }

    size_t getAmountOfBits() const{
        return amountOfBits;//Index start at zero...
    }
    /**
    *   Toggles the bit, Usefull for the CNOT Gate. 
    *   (Watch out if not done correctly assembling the bits will not reassemble)
    */
    void bitflip(const size_t bitChange){
        std::bitset<Globals::QUANTUM_INFINITY> bit(originalPos);
        bit[bitChange] = !bit[bitChange];
       // std::string decimal =  std::bitset<Globals::QUANTUM_INFINITY>(originalPos).to_string();
       // std::reverse(decimal.begin(), decimal.end());
   //     decimal[bitChange] = (decimal[bitChange == '0'])? '0' : '1';
     //   std::reverse(decimal.begin(), decimal.end());
       // std::bitset<Globals::QUANTUM_INFINITY> bit(decimal);
        originalPos =  (int)bit.to_ulong();
    }
    /**
    *   Allows you to do a function for each bit in the program
    */
    void forEachBit(std::function<void (const bool& bit, const size_t& pos)> bit){
        std::bitset<Globals::QUANTUM_INFINITY> bits(originalPos);
        for(size_t i = 0; i < getAmountOfBits(); i++){
            bit(bits[i], i);
        }
    }

    
    const size_t operator[] ( int bit) const{
        return std::bitset<Globals::QUANTUM_INFINITY>(originalPos)[bit];
    }

};

/**
*   Orders the bytes of a state. 
*   When the first bit is static on two bit state: [[00,01],[10,11]].
*   When the second bit is static on two bit state: [[00,10],[01,11]].
*   when the first bit is static on three bit state: [[000,001,010,011],[100,101,110,111]].
*   It will return always two vectors with the order
*/
std::vector<std::vector<ChanceOrder>> orderByBit(const size_t bit_index, const QuantumState& state){
    assertInput(bit_index > state.getAmountOfQBytes() - 1, "The control bit must be within range of the amount of qbits residing in this state..");
     std::vector<std::vector<ChanceOrder>> result;
    const QuantumData d = state.getState();
    const size_t amountOfQubits = state.getAmountOfQBytes();
    //Define the pattern.. 
    size_t divide = state.getAmountOfPossibilities();
    for(size_t i = bit_index + 1; i > 0; i--){
        divide /= 2;
    }

    std::vector<ChanceOrder> lh;
    std::vector<ChanceOrder> rh;

    for(size_t i = 0; i < d.rows() ; i += divide * 2){
        for(size_t j = i ; j < (divide + i); j++){
            lh.push_back(ChanceOrder(j, d(j,0),amountOfQubits));
        }
        for(size_t j = i + divide; j < ((divide * 2) + i); j++){
            rh.push_back(ChanceOrder(j,d(j,0),amountOfQubits));
        }
    }
    
    result.push_back(lh);
    result.push_back(rh);

    return result;

}

/**
*   Combines two vectors of merged data into one state.
*   Required after an orderbit operation.
*/
QuantumState mergeOrderProb(const std::vector<ChanceOrder>& lh, const std::vector<ChanceOrder>& rh){
    QuantumData res = QuantumData::Zero(lh.size() + rh.size(), 1);
    for(const ChanceOrder& b : lh){
        std::string d = std::bitset<Globals::QUANTUM_INFINITY>(b.originalPos).to_string();
        assertInput(res(b.originalPos,0) != 0.0, "Duplicate position.. This shouldn't happen: " + d );

        res(b.originalPos,0) = b.data;
    }
    for(const ChanceOrder& b : rh){
         std::string d = std::bitset<Globals::QUANTUM_INFINITY>(b.originalPos).to_string();
        assertInput(res(b.originalPos,0) != 0.0, "Duplicate position.. This shouldn't happen: " + d);
        res(b.originalPos,0) = b.data;
    }


    return QuantumState(res);
}




constexpr double F = 0.7071067811865476;

bool oppositeBitset(const ChanceOrder& lh, const ChanceOrder& rh, const size_t& targetBit){
    for(size_t i = 0; i < lh.getAmountOfBits(); i++){
        if(i == targetBit){
            if(lh[i] == rh[i]){
                return false; //that bit needs to be opposite..
            }
        } else {
            if(lh[i] != rh[i]){
                return false; //nope not the same
            }
        }
    }    
    return true;
}

void hadamardGate(const size_t& bit_index, QuantumState& state){
    assertInput(bit_index > state.getAmountOfQBytes() - 1, "The control bit must be within range of the amount of qbits residing in this state..");
    assertInput(!state.usable(), "This state has been entangled and can no longer be used seperatly");
    std::vector<ChanceOrder> everything;
    for(size_t i = 0; i < state.getAmountOfPossibilities(); i++){
        everything.push_back(ChanceOrder(i, state.getState()(i,0),state.getAmountOfQBytes()));
    }
    //std::cout << (state.getAmountOfQBytes() - bit_index ) << "\n";
    int index = (state.getAmountOfQBytes() - bit_index - 1 );
    std::vector<ChanceOrder> copy = everything;
    double d = F;//std::pow(2,-0.5);
    for(size_t i = 0; i < everything.size(); i++ ){
        for(size_t j = 0; j < everything.size(); j++){
            if(i == j){
                continue;
            } else {
                    if(oppositeBitset(copy[i], copy[j], index)){            
                        if(copy[i][index] == 0){
                            everything[i].data = d * copy[i].data + d * copy[j].data;
                        } else {
                            everything[i].data = d * copy[j].data - d * copy[i].data;
                        }
                    }
            }

        }
    }
    state = mergeOrderProb(everything, std::vector<ChanceOrder>());


}


void cnotGate(const size_t& control,const size_t& target, QuantumState& state){
    assertInput(control == target, "The control bit can't be the same as the target bit...");
    if(state.getAmountOfQBytes() == 2){
        quantumGate CNot = quantumGate::Zero(4,4);
        if(control == 0){
        CNot << 1, 0, 0, 0 , 
                0, 1, 0, 0,
                0, 0, 0, 1,
                0, 0, 1, 0;
        } 
        else{
            CNot << 
                1, 0, 0, 0 , 
                0, 0, 0, 1,
                0, 0, 1, 0,
                0, 1, 0, 0;
        }
        state =  CNot * state.getState();
    } else {

        std::vector<std::vector<ChanceOrder>>  order = orderByBit(control, state);
        std::vector<ChanceOrder> old(order[1]);

        for(size_t i = 0; i < order[1].size(); i++){
            
            order[1][i].bitflip( order[1][i].getAmountOfBits() -  target - 1 ); 
        }
        try{
            state = mergeOrderProb(order[0], order[1]);
        } catch(const InvalidInputException& ex){
            std::cout << "This error occured during control bit " << control << " and target : " << target << "\n"; 
            std::cout << "new - > old \n";
            for(size_t i = 0; i < order[1].size(); i++){
                std::cout << order[1][i] << " | " <<  old[i] <<"\n";
            }
            throw ex;
        }
        
    }
}


void pauliY(const size_t& bit_index, QuantumState& state){
    std::vector<ChanceOrder> everything;
    for(size_t i = 0; i < state.getAmountOfPossibilities(); i++){
        ChanceOrder ord(i, state.getState()(i,0),state.getAmountOfQBytes());
        if(ord[bit_index] == 1){
            ord.data = ord.data * std::complex<double>(0,-1);
        }
        everything.push_back(ord);
    }
    state = mergeOrderProb(everything, std::vector<ChanceOrder>());
}

void pauliZ(const size_t& bit_index, QuantumState& state){
    std::vector<ChanceOrder> everything;
    for(size_t i = 0; i < state.getAmountOfPossibilities(); i++){
        ChanceOrder ord(i, state.getState()(i,0),state.getAmountOfQBytes());
        if(ord[bit_index] == 0){
            ord.data =  -ord.data;
        }
        everything.push_back(ord);
    }
    state = mergeOrderProb(everything, std::vector<ChanceOrder>());

    
}

void pauliX(const size_t& bit_index, QuantumState& state){
    std::vector<ChanceOrder> everything;
    for(size_t i = 0; i < state.getAmountOfPossibilities(); i++){
        everything.push_back(ChanceOrder(i, state.getState()(i,0),state.getAmountOfQBytes()));
    }
    for(size_t i = 0; i < everything.size(); i++){
      //  std::cout <<  bit_index + 1 << "\n";
        everything[i].bitflip(everything[i].getAmountOfBits() -  bit_index - 1);
    }
    state = mergeOrderProb(everything, std::vector<ChanceOrder>());
}


int collapse(const QuantumState& state, std::default_random_engine& generator){
    const auto s = state.getState();
    
   // std::random_device rd;
 //   std::default_random_engine generator(rd());
    std::uniform_real_distribution<double> distribution(0.0,1.0);
    const double rand = distribution(generator);//Getting a random double between 0.0 and 

    int collapsedResult = 0;
    double sum = 0.0;
    // int t = 0;
    for(size_t i = 0; i < s.rows(); i++){
            collapsedResult++;
            double norm = std::norm(s(i,0));
            sum += norm;
            if(rand <= sum){
                return collapsedResult;
            }
    }
    std::cout << state << "\n";
    throw QuantumException("Could not collapse state!");
}

