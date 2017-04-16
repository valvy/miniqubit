#include "catch.hpp"
#include <QuantumState.hpp>
#include <Gates.hpp>
#include <iostream>
constexpr size_t MINIMAL_TEST_AMOUNT = 100;

TEST_CASE( "Grover algorithms") {
    /**
    *   Supplied algorithm from IBM
    *   https://quantumexperience.ng.bluemix.net/qstage/#/tutorial?sectionId=8443c4f713521c10b1a56a533958286b&pageIndex=2
    */
    std::random_device rd;
    std::default_random_engine generator(rd());
    SECTION("N=2 A=11"){
        QuantumState q0 = QuantumState::getZero();
        QuantumState q1 = QuantumState::getZero();
        QuantumState q2 = QuantumState::getZero();
        QuantumState ent(q0,q1);
        ent = QuantumState(ent,q2); //entangle them first :)
        hadamardGate(1, ent);
        hadamardGate(2, ent);
        hadamardGate(2, ent);
        cnotGate(1,2, ent);
        hadamardGate(2,ent);
        hadamardGate(1, ent);
        hadamardGate(2, ent);
        pauliX(1,ent);
        pauliX(2,ent);
        hadamardGate(2, ent);
        cnotGate(1,2, ent);
        hadamardGate(2,ent);
        pauliX(1, ent);
        pauliX(2, ent);
        hadamardGate(1, ent);
        hadamardGate(2, ent);
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            std::bitset<3> bitset = measure<3>(ent, generator);
            //std::cout << bitset << "\n";
            REQUIRE((bitset[0] == 1 && bitset[1] == 1 && bitset[2] == 0));//Answer is always 011
        }
    }

    SECTION("Multi7x13Mod15"){
        QuantumState q0 = QuantumState::getZero();
        QuantumState q1 = QuantumState::getZero();
        QuantumState q2 = QuantumState::getZero();
        QuantumState q3 = QuantumState::getZero();
        QuantumState q4 = QuantumState::getZero();
        QuantumState ent(q0,q1);
        ent = QuantumState(ent,q2); 
        ent = QuantumState(ent,q3);
        ent = QuantumState(ent,q4);  
        
        pauliX(1,ent);
        pauliX(2, ent);
        pauliX(4,ent);

        pauliX(1,ent);
        pauliX(2,ent);
        pauliX(3,ent);
        pauliX(4,ent);

        cnotGate(3,2, ent);
        cnotGate(2,3, ent);
        cnotGate(3,2, ent);

        cnotGate(2,1, ent);
        cnotGate(1,2, ent);
        cnotGate(2,1, ent);

        cnotGate(4,1, ent);
        cnotGate(1,4, ent);
        cnotGate(4,1, ent);
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            std::bitset<5> bitset = measure<5>(ent, generator);
            std::cout << bitset << "\n";
            REQUIRE((bitset[0] == 1 && bitset[1] == 0 && bitset[2] == 0 && bitset[3] == 0 && bitset[4] == 0));//Answer is always 011
        }
    }
}