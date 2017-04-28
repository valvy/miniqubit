#include "catch.hpp"
#include <MiniQbt.hpp>
//#include <iostream>


TEST_CASE( "Grover algorithms") {
    constexpr size_t MINIMAL_TEST_AMOUNT = 100;
    using namespace MiniQbt;
    std::random_device rd;
    std::default_random_engine generator(rd());
    typedef QuantumEmulator<5, false> DebugQuantum5;
    typedef QuantumEmulator<20, false> impossiblyBig;
    impossiblyBig big;
    auto b = big.generateRegister();

    constexpr char N_2_A_11[] = "N=2 A=11";
    SECTION(N_2_A_11){
        //return;
        DebugQuantum5 emulator;
        auto ent = emulator.generateRegister();
        
        //QuantumState ent(bitsize);
        emulator.hadamardGate(1, ent);
        emulator.hadamardGate(2, ent);
        emulator.hadamardGate(2, ent);
        emulator.controlledNot(1,2, ent);
        emulator.hadamardGate(2,ent);
        emulator.hadamardGate(1, ent);
        emulator.hadamardGate(2, ent);
        emulator.pauliX(1,ent);
        emulator.pauliX(2,ent);
        emulator.hadamardGate(2, ent);
        emulator.controlledNot(1,2, ent);
        emulator.hadamardGate(2,ent);
        emulator.pauliX(1, ent);
        emulator.pauliX(2, ent);
        emulator.hadamardGate(1, ent);
        emulator.hadamardGate(2, ent);
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            try{
            std::bitset<5> bitset = emulator.measure(ent, generator);
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
        DebugQuantum5 emulator;
        auto ent = emulator.generateRegister();
        emulator.hadamardGate(1, ent);
        emulator.hadamardGate(2, ent);
        emulator.phaseS(2,ent);
        emulator.hadamardGate(2, ent);
        emulator.controlledNot(1,2, ent);

        emulator.hadamardGate(2, ent);
        emulator.phaseS(2,ent);
        emulator.hadamardGate(1, ent);
        emulator.hadamardGate(2, ent);
        emulator.pauliX(1,ent);
        emulator.pauliX(2,ent);
        emulator.hadamardGate(2, ent);
        emulator.controlledNot(1,2, ent);

        emulator.hadamardGate(2, ent);
        emulator.pauliX(1,ent);
        emulator.pauliX(2,ent);
        emulator.hadamardGate(1, ent);
        emulator.hadamardGate(2, ent);

        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            std::bitset<5> bitset = emulator.measure(ent, generator);
             INFO("Answer that has been given: " << bitset);
          
            REQUIRE((bitset[0] == 0 && bitset[1] == 0 && bitset[2] == 0 && bitset[3] == 0 && bitset[4] == 0));
        }
    }
    
    SECTION("N=2 A=00"){
        return;
        DebugQuantum5 emulator;
        auto ent = emulator.generateRegister();
        emulator.hadamardGate(1, ent);
        emulator.hadamardGate(2, ent);
        emulator.hadamardGate(2, ent);
        emulator.phaseS(1,ent);
        emulator.phaseS(2,ent);
        emulator.hadamardGate(2,ent);
        emulator.controlledNot(1,2, ent);

        emulator.hadamardGate(2, ent);
        emulator.phaseS(1,ent);
        emulator.phaseS(2,ent);
        emulator.hadamardGate(1,ent);
        emulator.hadamardGate(2,ent);
        emulator.pauliX(1, ent);
        emulator.pauliX(2, ent);
        emulator.hadamardGate(2,ent);
        emulator.controlledNot(1,2, ent);

        emulator.hadamardGate(2,ent);
        emulator.pauliX(1, ent);
        emulator.pauliX(2, ent);
        emulator.hadamardGate(1,ent);
        emulator.hadamardGate(2,ent);
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            try{
                std::bitset<5> bitset = emulator.measure(ent, generator);
                INFO("N=2 A=00 failed because answer that has been given: " << bitset << " is wrong");
                REQUIRE((bitset[0] == 0 && bitset[1] == 0 && bitset[2] == 0 && bitset[3] == 0 && bitset[4] == 0));
            } catch(const QuantumException& exp){
                 FAIL("N=2 A=00 failed with the exception " << exp.getMessage() );
            }
        }
    }

}
//kaleidoscoop