#include "catch.hpp"
#include <miniqbt/intepreter/QasmAsyncIntepreter.hpp>
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

        REQUIRE(res[2] == 1);
        REQUIRE(!intepreter.hasErrors());
    }

    constexpr char ERROR_LINE_PROGRAM[] = "Error in program"; 
    SECTION(ERROR_LINE_PROGRAM){
        MiniQbt::QasmAsyncIntepreter intepreter;
        intepreter.intepret("qreg q[5];");
        intepreter.intepret("creg c[5];");
        intepreter.intepret("ERROR;");
        intepreter.intepret("measure q[0] -> c[0];");
        auto res = intepreter.readClassicRegister("c");
        REQUIRE(intepreter.hasErrors());
    }

    constexpr char MISSING_SEMICOLON[] = "missing semicolon"; 
    SECTION(MISSING_SEMICOLON){
        MiniQbt::QasmAsyncIntepreter intepreter;
        intepreter.intepret("qreg q[5];");
        intepreter.intepret("creg c[5];");
        intepreter.intepret("ERROR");
        intepreter.intepret("measure q[0] -> c[0];");
        auto res = intepreter.readClassicRegister("c");
        REQUIRE(intepreter.hasErrors());
    }


    constexpr char DOUBLE_EXPRESSIONS[] = "double expression"; 
    SECTION(DOUBLE_EXPRESSIONS){
        MiniQbt::QasmAsyncIntepreter intepreter;
        intepreter.intepret("qreg q[5]; creg c[5];");
        intepreter.intepret("x q[2];");
        intepreter.intepret("measure q[2] -> c[0];");
        auto res = intepreter.readClassicRegister("c");
        REQUIRE(res[0] == 1);
        REQUIRE(!intepreter.hasErrors());
    }

    constexpr char EMPTY_EXPRESSION[] = "Empty expression"; 
    SECTION(EMPTY_EXPRESSION){
        MiniQbt::QasmAsyncIntepreter intepreter;
        intepreter.intepret("qreg q[5]; creg c[5];");
        intepreter.intepret(";");//error
        intepreter.intepret("x q[2];");
        intepreter.intepret("measure q[0] -> c[0];");
        auto res = intepreter.readClassicRegister("c");
        REQUIRE(intepreter.hasErrors());
    }

    constexpr char EMPTY_EXPRESSION_WITH_SPACES[] = "Empty expression with spaces"; 
    SECTION(EMPTY_EXPRESSION_WITH_SPACES){
        MiniQbt::QasmAsyncIntepreter intepreter;
        intepreter.intepret("qreg q[5]; creg c[5];");
        intepreter.intepret("; ; ;;"); //annoying thing
        intepreter.intepret("x q[2];");
        intepreter.intepret("measure q[0] -> c[0];");
        auto res = intepreter.readClassicRegister("c");
        REQUIRE(intepreter.hasErrors());
    }

    constexpr char EXPRESSION_WITH_NLINE[] = "Expression with new line"; 
    SECTION(EXPRESSION_WITH_NLINE){
        MiniQbt::QasmAsyncIntepreter intepreter;
        intepreter.intepret("qreg q[5]; \n\n creg c[5];");
        intepreter.intepret("x q[2];");
        intepreter.intepret("measure q[0] -> c[0];");
        auto res = intepreter.readClassicRegister("c");
        REQUIRE(!intepreter.hasErrors());
    }
    constexpr char EXPRESSION_WITH_ONLY_NLINE[] = "Expression with only a new line"; 
    SECTION(EXPRESSION_WITH_NLINE){
        MiniQbt::QasmAsyncIntepreter intepreter;
        intepreter.intepret("qreg q[5];  creg c[5];");
        intepreter.intepret("\n");
        intepreter.intepret("measure q[0] -> c[0];");
        auto res = intepreter.readClassicRegister("c");
        REQUIRE(!intepreter.hasErrors());
    }
    constexpr char EXPRESSION_WITH_MORE_NLINE[] = "Expression with only and more then a new line"; 
    SECTION(EXPRESSION_WITH_MORE_NLINE){
        MiniQbt::QasmAsyncIntepreter intepreter;
        intepreter.intepret("qreg q[5];  creg c[5];");
        intepreter.intepret("\n\n");
        intepreter.intepret("measure q[0] -> c[0];");
        auto res = intepreter.readClassicRegister("c");
        REQUIRE(!intepreter.hasErrors());
    }

    constexpr char MULTI_LINE_EXPRESSION[] = "Expression with semicolon on new line"; 
    SECTION(MULTI_LINE_EXPRESSION){
        MiniQbt::QasmAsyncIntepreter intepreter;
        intepreter.intepret("qreg q[5] \n ;  creg c[5];");
        intepreter.intepret("measure q[0] -> c[0];");
        auto res = intepreter.readClassicRegister("c");
        REQUIRE(!intepreter.hasErrors());
    }

    constexpr char ONE_BIG_EXPRESSION[] = "Everything on one line"; 
    SECTION(ONE_BIG_EXPRESSION){
        MiniQbt::QasmAsyncIntepreter intepreter;
        intepreter.intepret( 
                            std::string("qreg q[5];              \n") +
                            std::string("creg c[5];              \n") +
                            std::string("x q[0]; x q[1];         \n") +
                            std::string("measure q[0] -> c[0]; measure q[1] -> c [1];  \n"));
        auto res = intepreter.readClassicRegister("c");
        REQUIRE(!intepreter.hasErrors());
        REQUIRE(res[0] == 1);
        REQUIRE(res[1] == 1);
        REQUIRE(res[2] == 0);
    }


}