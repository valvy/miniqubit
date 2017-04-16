
#include "catch.hpp"
#include <QuantumState.hpp>
#include <Gates.hpp>
constexpr size_t MINIMAL_TEST_AMOUNT = 100;

std::random_device rd;
std::default_random_engine generator(rd());


TEST_CASE( "Single hadamard" ) {
    QuantumState q1 = QuantumState::getZero();
    hadamardGate(0, q1); 
    hadamardGate(0, q1);//Reset :)
   
    for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
        
        std::bitset<1> bitset = measure<1>(q1, generator);
        REQUIRE(bitset[0] == 0);
    }
}


TEST_CASE( "hadamard with Controlled not") {
    SECTION("first qubit applied hadamard"){
        QuantumState q1 = QuantumState::getZero();
        QuantumState q2 = QuantumState::getZero();
        hadamardGate(0, q1); 
        QuantumState ent = QuantumState(q1, q2);
        cnotGate(0,1, ent);
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            std::bitset<2> bitset = measure<2>(ent, generator);
            REQUIRE(bitset[0] == bitset[1]);
        }
    }

    SECTION("Second qubit applied hadamard"){
        QuantumState q1 = QuantumState::getZero();
        QuantumState q2 = QuantumState::getZero();
        hadamardGate(0, q2); 
        QuantumState ent = QuantumState(q1, q2);
        cnotGate(0,1, ent);
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            std::bitset<2> bitset = measure<2>(ent, generator);
            REQUIRE(bitset[0] == 0); //other bit can be 1 :)
        }
    }

    SECTION("Quadruple hadamard with CNOT"){
        QuantumState q1 = QuantumState::getZero();
        QuantumState q2 = QuantumState::getZero();
       
        hadamardGate(0, q1); 
        hadamardGate(0, q2);
        QuantumState ent = QuantumState(q1, q2);
        cnotGate(0,1, ent);
        hadamardGate(0, ent);
        hadamardGate(1, ent); 
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            std::bitset<2> bitset = measure<2>(ent, generator);
            REQUIRE(bitset[0] == 0);
            REQUIRE(bitset[1] == 0);
        }
    }

    SECTION("Pauli x after hadamard and controlled not gate"){
        QuantumState q1 = QuantumState::getZero();
        QuantumState q2 = QuantumState::getZero();
        hadamardGate(0,q1);
        QuantumState ent(q1, q2);
        cnotGate(0,1, ent);
        pauliX(0, ent);
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            std::bitset<2> bitset = measure<2>(ent, generator);
            REQUIRE(bitset[0] != bitset[1]);//Bits are opposite of each other
        }
    }

    SECTION("Quadruple hadamard with in other order CNOT"){
        QuantumState q1 = QuantumState::getZero();
        QuantumState q2 = QuantumState::getZero();
       
        hadamardGate(0, q1); 
        hadamardGate(0, q2);
        QuantumState ent = QuantumState(q2, q1);
        cnotGate(0,1, ent);
        hadamardGate(1, ent);
        hadamardGate(0, ent); 
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            std::bitset<2> bitset = measure<2>(ent, generator);
            REQUIRE(bitset[0] == 0);
            REQUIRE(bitset[1] == 0);
        }
    }

    SECTION("Three qubits including hadamard and Pauli"){
        QuantumState q1 = QuantumState::getZero();
        QuantumState q2 = QuantumState::getZero();
        QuantumState q3 = QuantumState::getZero();
        hadamardGate(0,q1);
        hadamardGate(0,q2);
        hadamardGate(0,q3);
        QuantumState ent(q1, q2);
        cnotGate(0,1, ent);
        pauliX(0, ent);
        ent = QuantumState(ent,q3);
        hadamardGate(1,ent);
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            std::bitset<3> bitset = measure<3>(ent, generator);
            REQUIRE(bitset[1] == 0);//middle in this algorithm is always zero
        }
    }
}

