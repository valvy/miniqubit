#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>
#include <QuantumState.hpp>
#include <Gates.hpp>
//#include <iostream>

std::random_device rd;
std::default_random_engine generator(rd());

TEST_CASE( "Single hadamard", "[Hadamard]" ) {
    QuantumState q1 = QuantumState::getZero();
    hadamardGate(0, q1); 
    hadamardGate(0, q1);//Reset :)
   
    for(size_t i = 0; i < 100; i++){
        
        std::bitset<1> bitset = measure<1>(q1, generator);
        REQUIRE(bitset[0] == 0);
    }
}


TEST_CASE( "hadamard with Controlled not", "[Hadamard]" ) {
    SECTION("first qubit applied hadamard"){
        QuantumState q1 = QuantumState::getZero();
        QuantumState q2 = QuantumState::getZero();
        hadamardGate(0, q1); 
        QuantumState ent = QuantumState(q1, q2);
        cnotGate(0,1, ent);
        for(size_t i = 0; i < 100; i++){
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
        std::bitset<2> bitset = measure<2>(ent, generator);
        for(size_t i = 0; i < 100; i++){
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
        std::bitset<2> bitset = measure<2>(ent, generator);
        for(size_t i = 0; i < 100; i++){
            std::bitset<2> bitset = measure<2>(ent, generator);
            REQUIRE(bitset[0] == 0);
            REQUIRE(bitset[1] == 0);
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
        std::bitset<2> bitset = measure<2>(ent, generator);
        for(size_t i = 0; i < 100; i++){
            std::bitset<2> bitset = measure<2>(ent, generator);
            REQUIRE(bitset[0] == 0);
            REQUIRE(bitset[1] == 0);
        }
    }
}

