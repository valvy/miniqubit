#include "catch2/catch.hpp"
#include <miniqbt/emulator/MiniQbtEmulator.hpp>

TEST_CASE( "Bell tests") {
    
    constexpr size_t MINIMAL_TEST_AMOUNT = 10000;
    
    using namespace MiniQbt;
    typedef QuantumEmulator<2, false> DebugQuantum2;
    std::random_device rd;
    std::default_random_engine generator(rd());
    constexpr char BELL_STATE_ZW_MEASUREMENT[] = "Bell state ZW-Measurement";
    SECTION(BELL_STATE_ZW_MEASUREMENT){
        DebugQuantum2 emulator;
        auto ent = emulator.generateRegister();
        emulator.hadamardGate(0,ent);
        emulator.controlledNot(0,1, ent);
        emulator.phaseS(1,ent);
        emulator.hadamardGate(1,ent);
        emulator.phaseT(1, ent);
        emulator.hadamardGate(1,ent);
        std::pair<std::bitset<2>, size_t> first = std::make_pair(std::bitset<2>("00"),0);
        std::pair<std::bitset<2>, size_t> second = std::make_pair(std::bitset<2>("01"),0);
        std::pair<std::bitset<2>, size_t> third = std::make_pair(std::bitset<2>("10"),0);
        std::pair<std::bitset<2>, size_t> fourth = std::make_pair(std::bitset<2>("11"),0);
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            try{
                std::bitset<2> bitset = emulator.measure(ent, generator);
                if(bitset == first.first){
                    first.second++;
                } else if(bitset == second.first){
                    second.second++;
                } else if(bitset == third.first){
                    third.second++;
                } else if (bitset == fourth.first){
                    fourth.second++;
                }
            } catch(const QuantumException& exp){
                FAIL(BELL_STATE_ZW_MEASUREMENT << " failed with the exception " << exp.getMessage() );
            }
        }
        REQUIRE((first.second > second.second));
        REQUIRE((first.second > third.second));
        REQUIRE((fourth.second > second.second));
        REQUIRE((fourth.second > third.second));

    }


    constexpr char BELL_STATE_ZV_MEASUREMENT[] = "Bell state ZV-Measurement";
    SECTION(BELL_STATE_ZV_MEASUREMENT){
        DebugQuantum2 emulator;
        auto ent = emulator.generateRegister();
        emulator.hadamardGate(0,ent);
        emulator.controlledNot(0,1, ent);
        emulator.phaseS(1,ent);
        emulator.hadamardGate(1,ent);
        emulator.phaseTDG(1, ent);
        emulator.hadamardGate(1,ent);
        std::pair<std::bitset<2>, size_t> first = std::make_pair(std::bitset<2>("00"),0);
        std::pair<std::bitset<2>, size_t> second = std::make_pair(std::bitset<2>("01"),0);
        std::pair<std::bitset<2>, size_t> third = std::make_pair(std::bitset<2>("10"),0);
        std::pair<std::bitset<2>, size_t> fourth = std::make_pair(std::bitset<2>("11"),0);
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            try{
                std::bitset<2> bitset = emulator.measure(ent, generator);
                if(bitset == first.first){
                    first.second++;
                } else if(bitset == second.first){
                    second.second++;
                } else if(bitset == third.first){
                    third.second++;
                } else if (bitset == fourth.first){
                    fourth.second++;
                }
            } catch(const QuantumException& exp){
                FAIL(BELL_STATE_ZV_MEASUREMENT << " failed with the exception " << exp.getMessage() );
            }
        }
        REQUIRE((first.second > second.second));
        REQUIRE((first.second > third.second));
        REQUIRE((fourth.second > second.second));
        REQUIRE((fourth.second > third.second));
    }

    constexpr char BELL_STATE_XW_MEASUREMENT[] = "Bell state XW-Measurement";
    SECTION(BELL_STATE_XW_MEASUREMENT){
        DebugQuantum2 emulator;
        auto ent = emulator.generateRegister();
        emulator.hadamardGate(0,ent);
        emulator.controlledNot(0,1, ent);
        emulator.hadamardGate(0,ent);
        emulator.phaseS(1,ent);
        emulator.hadamardGate(1,ent);
        emulator.phaseT(1, ent);
        emulator.hadamardGate(1,ent);
        std::pair<std::bitset<2>, size_t> first = std::make_pair(std::bitset<2>("00"),0);
        std::pair<std::bitset<2>, size_t> second = std::make_pair(std::bitset<2>("01"),0);
        std::pair<std::bitset<2>, size_t> third = std::make_pair(std::bitset<2>("10"),0);
        std::pair<std::bitset<2>, size_t> fourth = std::make_pair(std::bitset<2>("11"),0);
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            try{
                std::bitset<2> bitset = emulator.measure(ent, generator);
                if(bitset == first.first){
                    first.second++;
                } else if(bitset == second.first){
                    second.second++;
                } else if(bitset == third.first){
                    third.second++;
                } else if (bitset == fourth.first){
                    fourth.second++;
                }
            } catch(const QuantumException& exp){
                FAIL(BELL_STATE_XW_MEASUREMENT << " failed with the exception " << exp.getMessage() );
            }
        }
        REQUIRE((first.second > second.second));
        REQUIRE((first.second > third.second));
        REQUIRE((fourth.second > second.second));
        REQUIRE((fourth.second > third.second));
    }

    constexpr char BELL_STATE_XV_MEASUREMENT[] = "Bell state XV-Measurement";
    SECTION(BELL_STATE_XV_MEASUREMENT){
        DebugQuantum2 emulator;
        auto ent = emulator.generateRegister();
        emulator.hadamardGate(0,ent);
        emulator.controlledNot(0,1, ent);
        emulator.hadamardGate(0,ent);
        emulator.phaseS(1,ent);
        emulator.hadamardGate(1,ent);
        emulator.phaseTDG(1, ent);
        emulator.hadamardGate(1,ent);
        std::pair<std::bitset<2>, size_t> first = std::make_pair(std::bitset<2>("00"),0);
        std::pair<std::bitset<2>, size_t> second = std::make_pair(std::bitset<2>("01"),0);
        std::pair<std::bitset<2>, size_t> third = std::make_pair(std::bitset<2>("10"),0);
        std::pair<std::bitset<2>, size_t> fourth = std::make_pair(std::bitset<2>("11"),0);
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            try{
                std::bitset<2> bitset = emulator.measure(ent, generator);
                if(bitset == first.first){
                    first.second++;
                } else if(bitset == second.first){
                    second.second++;
                } else if(bitset == third.first){
                    third.second++;
                } else if (bitset == fourth.first){
                    fourth.second++;
                }
            } catch(const QuantumException& exp){
                FAIL(BELL_STATE_XW_MEASUREMENT << " failed with the exception " << exp.getMessage() );
            }
        }
        REQUIRE((first.second < second.second));
        REQUIRE((first.second < third.second));
        REQUIRE((fourth.second < second.second));
        REQUIRE((fourth.second < third.second));

    }


}