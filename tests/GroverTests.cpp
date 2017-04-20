#include "catch.hpp"
#include <QuantumState.hpp>
#include <Gates.hpp>
#include <iostream>


TEST_CASE( "Grover algorithms") {
    constexpr size_t MINIMAL_TEST_AMOUNT = 100;

    std::random_device rd;
    std::default_random_engine generator(rd());

    constexpr char N_2_A_11[] = "N=2 A=11";
    SECTION(N_2_A_11){
        //return;
        constexpr size_t bitsize = 5;
        QuantumState ent(bitsize);
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
            try{
            std::bitset<bitsize> bitset = measure<bitsize>(ent, generator);
            INFO(N_2_A_11 <<" failed because answer that has been given: " << bitset << " is wrong");
            REQUIRE((bitset[4] == 0 && bitset[3] == 1 && bitset[2] == 1));//Answer is always 011
            } catch(const QuantumException& exp){
                 FAIL(N_2_A_11 << " failed with the exception " << exp.getMessage() );
            }

        }
    }

    constexpr char N_2_A_01[] = "N=2 A=01";
    SECTION(N_2_A_01){
        return;
       // return;
        constexpr size_t bitsize = 5;
        QuantumState ent(bitsize);
        hadamardGate(1, ent);
        hadamardGate(2, ent);
        phaseS(2,ent);
        hadamardGate(2, ent);
        cnotGate(1,2, ent);

        hadamardGate(2, ent);
        phaseS(2,ent);
        hadamardGate(1, ent);
        hadamardGate(2, ent);
        pauliX(1,ent);
        pauliX(2,ent);
        hadamardGate(2, ent);
        cnotGate(1,2, ent);

        hadamardGate(2, ent);
        pauliX(1,ent);
        pauliX(2,ent);
        hadamardGate(1, ent);
        hadamardGate(2, ent);

        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            std::bitset<bitsize> bitset = measure<bitsize>(ent, generator);
            // INFO("Answer that has been given: " << bitset);
            std::cout << bitset << "\n";
        //    REQUIRE((bitset[0] == 0 && bitset[1] == 0 && bitset[2] == 0 && bitset[3] == 0 && bitset[4] == 0));
        }
    }

    SECTION("N=2 A=00"){
        return;
        constexpr size_t bitsize = 5;
        QuantumState ent(bitsize);
        hadamardGate(1, ent);
        hadamardGate(2, ent);
        hadamardGate(2, ent);
        phaseS(1,ent);
        phaseS(2,ent);
        hadamardGate(2,ent);
        cnotGate(1,2, ent);

        hadamardGate(2, ent);
        phaseS(1,ent);
        phaseS(2,ent);
        hadamardGate(1,ent);
        hadamardGate(2,ent);
        pauliX(1, ent);
        pauliX(2, ent);
        hadamardGate(2,ent);
        cnotGate(1,2, ent);

        hadamardGate(2,ent);
        pauliX(1, ent);
        pauliX(2, ent);
        hadamardGate(1,ent);
        hadamardGate(2,ent);
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            try{
                std::bitset<bitsize> bitset = measure<bitsize>(ent, generator);
                INFO("N=2 A=00 failed because answer that has been given: " << bitset << " is wrong");
                REQUIRE((bitset[0] == 0 && bitset[1] == 0 && bitset[2] == 0 && bitset[3] == 0 && bitset[4] == 0));
            } catch(const QuantumException& exp){
                 FAIL("N=2 A=00 failed with the exception " << exp.getMessage() );
            }
        }
    }

}
//kaleidoscoop