#include "catch.hpp"
#include <miniqbt/emulator/MiniQbtEmulator.hpp>
#include <iostream>

void first(
    MiniQbt::Core::QuantumState<3>& ent, 
    const MiniQbt::QuantumEmulator<3,false>& emulator){

    emulator.hadamardGate(0,ent);
    emulator.hadamardGate(1,ent);
    emulator.pauliX(2,ent);
    emulator.controlledNot(1,2, ent);
    emulator.controlledNot(0,2, ent);
    emulator.hadamardGate(0,ent);
    emulator.hadamardGate(1,ent);
    emulator.hadamardGate(2,ent);
}


void ending(
    MiniQbt::Core::QuantumState<3>& ent, 
    const MiniQbt::QuantumEmulator<3,false>& emulator,
    std::string testName,
    const size_t minimal_test_amount){
        std::random_device rd;
        std::default_random_engine generator(rd());
        
        std::pair<std::bitset<3>, size_t> first = std::make_pair(std::bitset<3>("000"),0);
        std::pair<std::bitset<3>, size_t> second = std::make_pair(std::bitset<3>("011"),0);
        std::pair<std::bitset<3>, size_t> third = std::make_pair(std::bitset<3>("101"),0);
        std::pair<std::bitset<3>, size_t> fourth = std::make_pair(std::bitset<3>("110"),0);
        for(size_t i = 0; i < minimal_test_amount; i++){
            try{
                std::bitset<3> bitset = emulator.measure(ent, generator);
                if(bitset == first.first){
                    first.second++;
                } else if(bitset == second.first){
                    second.second++;
                } else if(bitset == third.first){
                    third.second++;
                } else if(bitset == fourth.first){
                    fourth.second++;
                } else {
                    FAIL(testName << " failed because an invalid result is given" );
                }
            } catch(const MiniQbt::QuantumException& exp){
                FAIL(testName << " failed with the exception " << exp.getMessage() );
            }
        }
    }

TEST_CASE( "GHZ States") {
    constexpr size_t MINIMAL_TEST_AMOUNT = 10000;
    using namespace MiniQbt;
    typedef QuantumEmulator<3, false> DebugQuantum3;
    std::random_device rd;
    std::default_random_engine generator(rd());

    constexpr char THREE_Q_GHZ_STATE[] = "3Q GHZ state";
    SECTION(THREE_Q_GHZ_STATE){
        DebugQuantum3 emulator;
        auto ent = emulator.generateRegister();
        first(ent, emulator);
        std::pair<std::bitset<3>, size_t> first = std::make_pair(std::bitset<3>("000"),0);
        std::pair<std::bitset<3>, size_t> second = std::make_pair(std::bitset<3>("111"),0);
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            try{
                std::bitset<3> bitset = emulator.measure(ent, generator);
                if(bitset == first.first){
                    first.second++;
                } else if(bitset == second.first){
                    second.second++;
                } else{
                    FAIL(THREE_Q_GHZ_STATE << " failed because an invalid result is given" );
                }
            } catch(const QuantumException& exp){
                FAIL(THREE_Q_GHZ_STATE << " failed with the exception " << exp.getMessage() );
            }
        }
    }

    constexpr char THREE_Q_GHZ_STATE_YYX_MEASUREMENT[] = "3Q GHZ state YYX-Measurement";
    SECTION(THREE_Q_GHZ_STATE_YYX_MEASUREMENT){
        DebugQuantum3 emulator;
        auto ent = emulator.generateRegister();
        first(ent,emulator);
    
        //barrier ???

        emulator.phaseSDG(0,ent);
        emulator.phaseSDG(1,ent);
        emulator.hadamardGate(0,ent);
        emulator.hadamardGate(1,ent);
        emulator.hadamardGate(2,ent);

        ending(
            ent,
            emulator,
            std::string(THREE_Q_GHZ_STATE_YYX_MEASUREMENT),
            MINIMAL_TEST_AMOUNT
            );
    
    }

    constexpr char THREE_Q_GHZ_STATE_YXY_MEASUREMENT[] = "3Q GHZ state XYY-Measurement";
    SECTION(THREE_Q_GHZ_STATE_YXY_MEASUREMENT){
        DebugQuantum3 emulator;
        auto ent = emulator.generateRegister();
        first(ent,emulator);
    
        emulator.phaseSDG(0,ent);
        emulator.phaseSDG(2,ent);
        emulator.hadamardGate(0,ent);
        emulator.hadamardGate(1,ent);
        emulator.hadamardGate(2,ent);
        ending(
            ent,
            emulator,
            std::string(THREE_Q_GHZ_STATE_YXY_MEASUREMENT),
            MINIMAL_TEST_AMOUNT);

    }


    constexpr char THREE_Q_GHZ_STATE_XYY_MEASUREMENT[] = "3Q GHZ state XYY-Measurement";
        SECTION(THREE_Q_GHZ_STATE_XYY_MEASUREMENT){
            DebugQuantum3 emulator;
            auto ent = emulator.generateRegister();
            first(ent,emulator);
        
            emulator.phaseSDG(1,ent);
            emulator.phaseSDG(2,ent);
            emulator.hadamardGate(0,ent);
            emulator.hadamardGate(1,ent);
            emulator.hadamardGate(2,ent);
            ending(
                ent,
                emulator,
                std::string(THREE_Q_GHZ_STATE_XYY_MEASUREMENT),
                MINIMAL_TEST_AMOUNT);
        }

        constexpr char THREE_Q_GHZ_STATE_XXX_MEASUREMENT[] = "3Q GHZ state XXX-Measurement";
        SECTION(THREE_Q_GHZ_STATE_XXX_MEASUREMENT){
            DebugQuantum3 emulator;
            auto ent = emulator.generateRegister();
            first(ent,emulator);
            emulator.hadamardGate(0,ent);
            emulator.hadamardGate(1,ent);
            emulator.hadamardGate(2,ent);
            std::pair<std::bitset<3>, size_t> first = std::make_pair(std::bitset<3>("001"),0);
            std::pair<std::bitset<3>, size_t> second = std::make_pair(std::bitset<3>("010"),0);
            std::pair<std::bitset<3>, size_t> third = std::make_pair(std::bitset<3>("111"),0);
            std::pair<std::bitset<3>, size_t> fourth = std::make_pair(std::bitset<3>("100"),0);
            for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
                try{
                    std::bitset<3> bitset = emulator.measure(ent, generator);
                    if(bitset == first.first){
                        first.second++;
                    } else if(bitset == second.first){
                        second.second++;
                    } else if(bitset == third.first){
                        third.second++;
                    } else if(bitset == fourth.first){
                        fourth.second++;
                    } else {
                        FAIL(THREE_Q_GHZ_STATE_XXX_MEASUREMENT << " failed because an invalid result is given" );
                    }
                } catch(const MiniQbt::QuantumException& exp){
                    FAIL(THREE_Q_GHZ_STATE_XXX_MEASUREMENT << " failed with the exception " << exp.getMessage() );
                }
            }
        }
}