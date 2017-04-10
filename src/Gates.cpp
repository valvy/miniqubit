#include "Gates.hpp"
#include "Globals.hpp"
#include <vector>
#include <iostream>
#include <unsupported/Eigen/KroneckerProduct>
#include "Utils.hpp"

/**
*   Small struct to easily disassemble and reassemble bit orders of the program.
*   Might not be the best and fastest solution but it does get the job done.
*   This will however allow me to make infinite big quantum computer :D
*/
struct ChanceOrder{
    size_t originalPos;
    std::complex<double> data;
    ChanceOrder(size_t originalPos, const std::complex<double>& data) : originalPos(originalPos), data(data) {}
    friend std::ostream& operator<<(std::ostream& os, const ChanceOrder& state){
        os << state.data << " : "<< std::bitset<Globals::QUANTUM_INFINITY>(state.originalPos);
        return os;
    }
    /**
    *   Toggles the bit, Usefull for the CNOT Gate. 
    *   (Watch out if not done correctly assembling the bits will not reassemble)
    */
    void bitflip(const size_t bitChange){
        std::bitset<Globals::QUANTUM_INFINITY> bit(originalPos);
        bit[bitChange] = (bit[bitChange] == 0)? 1 : 0; //toggles the bit (Muwhahahaha)
        this->originalPos = (int)bit.to_ulong();
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

    //Define the pattern.. 
    size_t divide = state.getAmountOfPossibilities();
    for(size_t i = bit_index + 1; i > 0; i--){
        divide /= 2;
    }

    std::vector<ChanceOrder> lh;
    std::vector<ChanceOrder> rh;

    for(size_t i = 0; i < d.rows() ; i += divide * 2){
        for(size_t j = i ; j < (divide + i); j++){
            lh.push_back(ChanceOrder(j, d(j,0)));
        }
        for(size_t j = i + divide; j < ((divide * 2) + i); j++){
            rh.push_back(ChanceOrder(j,d(j,0)));
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
        res(b.originalPos,0) = b.data;
    }
    for(const ChanceOrder& b : rh){
        res(b.originalPos,0) = b.data;
    }


    return QuantumState(res);
}

/**
*
*/

constexpr double F = 0.7071067811865476;


/**
*   Applies the hadamard gate 
*/
void applyHadamard(std::vector<ChanceOrder>& hand){
    std::vector<ChanceOrder> res;
    for(size_t i = 0; i < (hand.size() / 2); i++){
        std::complex<double> temp;
        temp = F * hand[i].data;
        for(size_t j = 0; j < hand.size(); j++){
            if(j != i){
                temp += F * hand[j].data;
            }
            
        }
        res.push_back(ChanceOrder(hand[i].originalPos, temp));
    }
    
    for(size_t i = (hand.size() / 2); i < hand.size(); i++){
        std::complex<double> temp;
        temp -= F * hand[i].data;
        for(size_t j = 0; j < hand.size(); j++){
            if(j != i){
                temp -= (F * hand[j].data);
            }
            
        }

        res.push_back(ChanceOrder(hand[i].originalPos, temp));
    }
    hand = res;
}

void hadamardGate(const size_t& bit_index, QuantumState& state){
    assertInput(bit_index > state.getAmountOfQBytes() - 1, "The control bit must be within range of the amount of qbits residing in this state..");
    assertInput(!state.usable(), "This state has been entangled and can no longer be used seperatly");
    if(state.getAmountOfQBytes() == 1){
        quantumGate Hadamard = quantumGate::Zero(2,2);
        Hadamard << 1 ,1 , 1 , -1;
        Hadamard = (F * Hadamard);
        state =  Hadamard * state.getState() ;
    } else {  
        auto order = orderByBit(bit_index, state);
        applyHadamard(order[0]);
        applyHadamard(order[1]);
        state = mergeOrderProb(order[0], order[1]);
    }
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
        //First get control bit
        std::vector<std::vector<ChanceOrder>>  order = orderByBit(control, state);
        //Since the first is always zero, don't do anything with it. (zero will never be flipped)
   
        for(size_t i = 0; i < order[1].size(); i++){
            //Just nasty flip the corresponding bit
            //The order of values will change. Muwahaha
            order[1][i].bitflip(target); 
        }


        state = mergeOrderProb(order[0], order[1]);
    }
}

void pauliX(const size_t& bit_index, QuantumState& state){
    throw QuantumException("Not yet implemented....");
}


int collapse(const QuantumState& state){
    const auto s = state.getState();
    
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<double> distribution(0.0,1.0);
    const double rand = distribution(generator);//Getting a random double between 0.0 and 

    int collapsedResult = 0;
    double sum = 0.0;
    // int t = 0;
    for(size_t i = 0; i < s.rows(); i++){
            collapsedResult++;
            double norm = std::norm(s(i,0));
            sum += norm;
            if(rand < sum){
                return collapsedResult;
            }
    }
    std::cout << state << "\n";
    throw QuantumException("Could not collapse state!");
}

