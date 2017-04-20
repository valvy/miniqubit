#include "catch.hpp"
#include <QuantumState.hpp>
#include <Gates.hpp>
#include <iostream>

TEST_CASE( "Shor algorithms") {
    constexpr size_t MINIMAL_TEST_AMOUNT = 100;
    /**
    *   Supplied algorithm from IBM
    *   https://quantumexperience.ng.bluemix.net/qstage/#/tutorial?sectionId=8443c4f713521c10b1a56a533958286b&pageIndex=2
    */
    std::random_device rd;
    std::default_random_engine generator(rd());
    constexpr char MULTI_7_X_13_MOD_15_NAME[] = "Multi7x13Mod15";
    SECTION(MULTI_7_X_13_MOD_15_NAME){
        QuantumState ent(5);
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
            try{
                std::bitset<5> bitset = measure<5>(ent, generator);
                INFO(MULTI_7_X_13_MOD_15_NAME <<" failed because answer that has been given: " << bitset << " is wrong");
                REQUIRE((bitset[4] == 0 && bitset[3] == 0 && bitset[2] == 0 && bitset[1] == 0 && bitset[0] == 1));
            } catch(const QuantumException& exp){
                FAIL(MULTI_7_X_13_MOD_15_NAME << " failed with the exception " << exp.getMessage() );
            }
        }
    }

}