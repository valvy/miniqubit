#include "catch.hpp"
#include <miniqbt/emulator/MiniQbtEmulator.hpp>

TEST_CASE( "Basic circuits algorithms") {

    constexpr size_t MINIMAL_TEST_AMOUNT = 100;
    
    using namespace MiniQbt;
    typedef QuantumEmulator<2, false> DebugQuantum2;
    typedef QuantumEmulator<3, false> DebugQuantum3;
    std::random_device rd;
    std::default_random_engine generator(rd());


    constexpr char REVERSED_CNOT[] = "Reversed CNOT";
    
    SECTION(REVERSED_CNOT){
        DebugQuantum2 emulator;
        auto ent = emulator.generateRegister();
        emulator.pauliX(1,ent);
        emulator.hadamardGate(0,ent);
        emulator.hadamardGate(1,ent);
        emulator.controlledNot(0,1, ent);
        emulator.hadamardGate(0,ent);
        emulator.hadamardGate(1,ent);
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            try{
                std::bitset<2> bitset = emulator.measure(ent, generator);
                INFO(REVERSED_CNOT <<" failed because answer that has been given: " << bitset << " is wrong");
                REQUIRE((bitset[0] == 1 && bitset[1] == 1));
            } catch(const QuantumException& exp){
                FAIL(REVERSED_CNOT << " failed with the exception " << exp.getMessage() );
            }

        }
    }

    constexpr char SWAP_GATE[] = "Swap gate";
    SECTION(SWAP_GATE){
        DebugQuantum2 emulator;
        auto ent = emulator.generateRegister();
        emulator.pauliX(1,ent);
        emulator.controlledNot(0,1, ent);
        emulator.hadamardGate(0,ent);
        emulator.hadamardGate(1,ent);
        emulator.controlledNot(0,1, ent);
        emulator.hadamardGate(0,ent);
        emulator.hadamardGate(1,ent);
        emulator.controlledNot(0,1, ent);
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            try{
                std::bitset<2> bitset = emulator.measure(ent, generator);
                INFO(SWAP_GATE <<" failed because answer that has been given: " << bitset << " is wrong");
                REQUIRE((bitset[0] == 0 && bitset[1] == 1));
            } catch(const QuantumException& exp){
                FAIL(SWAP_GATE << " failed with the exception " << exp.getMessage() );
            }

        }
    }

    constexpr char SWAP_Q0_AND_Q1[] = "swap q0 and q1";

    SECTION(SWAP_Q0_AND_Q1){
        DebugQuantum3 emulator;
        auto ent = emulator.generateRegister();
        emulator.hadamardGate(0,ent);
        emulator.controlledNot(0,2, ent);
        
        emulator.hadamardGate(0,ent);
        emulator.hadamardGate(2,ent);
        emulator.controlledNot(0,2, ent);

        emulator.hadamardGate(0,ent);
        emulator.hadamardGate(2,ent);
        emulator.controlledNot(0,2, ent);
        emulator.controlledNot(1,2, ent);

        emulator.hadamardGate(1,ent);
        emulator.hadamardGate(2,ent);
        emulator.controlledNot(1,2, ent);
        emulator.hadamardGate(1,ent);
        emulator.hadamardGate(2,ent);
       
        emulator.controlledNot(1,2, ent);
        emulator.controlledNot(0,2, ent);

        emulator.hadamardGate(0,ent);
        emulator.hadamardGate(2,ent);

        emulator.controlledNot(0,2, ent);

        
        emulator.hadamardGate(0,ent);
        emulator.hadamardGate(2,ent);

        emulator.controlledNot(0,2, ent);

        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            try{
                std::bitset<3> bitset = emulator.measure(ent, generator);
                INFO(SWAP_Q0_AND_Q1 <<" failed because answer that has been given: " << bitset << " is wrong");
                REQUIRE((bitset[0] == 0 && bitset[2] == 0));
            } catch(const QuantumException& exp){
                FAIL(SWAP_Q0_AND_Q1 << " failed with the exception " << exp.getMessage() );
            }

        }
    }
}