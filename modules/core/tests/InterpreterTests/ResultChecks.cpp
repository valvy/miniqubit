#include "catch2/catch.hpp"
#include <miniqbt/MiniQbt.hpp>
#include <iostream>
#include <sstream>
TEST_CASE( "Result checks") {

    std::random_device rd;
    std::default_random_engine generator(rd());

    constexpr char CHECK_MIRROR [] = "Checking if calculations aren't mirrored";
    SECTION(CHECK_MIRROR){
        //The interpreter
        const char* src = 
        "qreg a[5]; creg b[5];"
        "x a[0];"
        "measure a[0] -> b[0];"
        "measure a[1] -> b[1];"
        "measure a[2] -> b[2];"
        "measure a[3] -> b[3];"
        "measure a[4] -> b[4];";

        MiniQbt::QasmAsyncInterpreter interpreter;
        interpreter.interpret(std::string(src));
        auto res = interpreter.readClassicRegister("b");
        REQUIRE(!interpreter.hasErrors());

        constexpr size_t REGISTER_SIZE = 5;
        MiniQbt::QuantumEmulator<REGISTER_SIZE,true> emulator;
        auto ent = emulator.generateRegister();
        emulator.pauliX(0, ent);
        std::bitset<REGISTER_SIZE> bitset = emulator.measure(ent, generator);
        
        std::stringstream ss;
        ss << CHECK_MIRROR << " answer from the interpreter was : " ;
        for(const bool d : res){
            ss << d;
        }
        ss << " while the answer from the emulator was ";
        for(size_t i = 0; i < REGISTER_SIZE; i++){
            ss << bitset[i];
        }

        INFO(ss.str());
        for(size_t i = 0; i < REGISTER_SIZE; i++){
            REQUIRE(res[i] == bitset[i]);
        }
    }


    constexpr char MEASURE_CHECK[] = "Checking measure";
    SECTION(MEASURE_CHECK){
        //The interpreter
        const char* src = 
        "qreg a[5]; creg b[5];"
        "x a[0]; x a[2]; x a[4];"
        "measure a[0] -> b[0];"
        "measure a[1] -> b[1];"
        "measure a[2] -> b[2];"
        "measure a[3] -> b[3];"
        "measure a[4] -> b[4];";

        MiniQbt::QasmAsyncInterpreter interpreter;
        interpreter.interpret(std::string(src));
        auto res = interpreter.readClassicRegister("b");
        REQUIRE(!interpreter.hasErrors());
       
        constexpr size_t REGISTER_SIZE = 5;
        MiniQbt::QuantumEmulator<REGISTER_SIZE,true> emulator;
        auto ent = emulator.generateRegister();
        emulator.pauliX(0, ent);
        emulator.pauliX(2, ent);
        emulator.pauliX(4, ent);
        std::bitset<REGISTER_SIZE> bitset = emulator.measure(ent, generator);

        for(size_t i = 0; i < REGISTER_SIZE; i++){
            REQUIRE(res[i] == bitset[i]);
        }
    }

}