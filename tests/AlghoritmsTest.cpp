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
            REQUIRE((bitset[2] == 0 && bitset[1] == 1 && bitset[0] == 1));//Answer is always 011
        }
    }
}