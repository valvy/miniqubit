#include "catch.hpp"
#include <QasmAsyncIntepreter.hpp>
#include <iostream>

TEST_CASE( "Asyncronous coding tests") {
    
    constexpr char ONE_PAULI[] = "One PauliX test";
    SECTION(ONE_PAULI){
        MiniQbt::QasmAsyncIntepreter intepreter;
        intepreter.intepret("qreg q[5];");
        intepreter.intepret("creg c[5];");
        intepreter.intepret("x q[2];");
        intepreter.intepret("measure q[0] -> c[0];");
        intepreter.intepret("measure q[1] -> c[1];");
        intepreter.intepret("measure q[2] -> c[2];");
        intepreter.intepret("measure q[3] -> c[3];");
        intepreter.intepret("measure q[4] -> c[4];");
        auto res = intepreter.readClassicRegister("c");
        REQUIRE(!intepreter.hasErrors());
    }

    constexpr char ERROR_LINE_PROGRAM[] = "Error in program"; 
    SECTION(ERROR_LINE_PROGRAM){
        MiniQbt::QasmAsyncIntepreter intepreter;
        intepreter.intepret("qreg q[5];");
        intepreter.intepret("creg c[5];");
        intepreter.intepret("xd q[2];");
        intepreter.intepret("measure q[0] -> c[0];");
        auto res = intepreter.readClassicRegister("c");
        REQUIRE(intepreter.hasErrors());
    }
}