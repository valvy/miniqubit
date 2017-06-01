#include "catch.hpp"
#include <miniqbt/emulator/MiniQbtEmulator.hpp>


TEST_CASE( "Learning parity with noise") {
    constexpr size_t MINIMAL_TEST_AMOUNT = 100;
    using namespace MiniQbt;
    typedef QuantumEmulator<5, false> DebugQuantum5;
    std::random_device rd;
    std::default_random_engine generator(rd());

    constexpr char LPN_CIRCUIT_2[] = "Lpn circuit 2";
    SECTION(LPN_CIRCUIT_2){
        DebugQuantum5 emulator;
        auto ent = emulator.generateRegister();
        emulator.hadamardGate(0,ent);
        emulator.hadamardGate(1,ent);
        emulator.hadamardGate(3,ent);
        emulator.hadamardGate(4,ent);

        emulator.controlledNot(3,2, ent);
        emulator.controlledNot(0,2, ent);

        emulator.hadamardGate(0,ent);
        emulator.hadamardGate(1,ent);
        emulator.hadamardGate(2,ent);
        emulator.hadamardGate(3,ent);
        emulator.hadamardGate(4,ent);

        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            try{
                std::bitset<5> bitset = emulator.measure(ent, generator);
                INFO(LPN_CIRCUIT_2 <<" failed because answer that has been given: " << bitset << " is wrong");
                REQUIRE((bitset[0] == 0 && bitset[3] == 0 && bitset[1] == bitset[2] && bitset[2] == bitset[4]));
            } catch(const QuantumException& exp){
                FAIL(LPN_CIRCUIT_2 << " failed with the exception " << exp.getMessage() );
            }

        }
    }

}