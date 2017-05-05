#include "catch.hpp"
#include <miniqbt/intepreter/QasmAsyncIntepreter.hpp>
#include <sstream>

TEST_CASE( "Syntax tests") {
    
    constexpr char PAULI_SYNTAX[] = "All Pauli gates";
    SECTION(PAULI_SYNTAX){
        //Checking if the syntax with all the pauli gates works
        MiniQbt::QasmAsyncIntepreter intepreter;
        const char * src = 
        "// a comment               \n"
        "OPENQASM 2.0;              \n"
        "include \"qelib1.inc\";    \n"
        "qreg q[5]; creg c[5];      \n"
        "x q[0]; y q[1]; z q[2];    \n"
        "measure q[1] -> c[1];      \n"
        "measure q[2] -> c[2];      \n";
        intepreter.intepret(std::string(src));
        auto res = intepreter.readClassicRegister("c");
        const bool failed = intepreter.hasErrors();
        std::stringstream ss;
        ss << "Test : " << PAULI_SYNTAX << " Failed with errors: \n";
        while(intepreter.hasErrors()){
            ss << intepreter.getError() << "\n";
        }

        INFO(ss.str());
        REQUIRE(!failed);
    }

    constexpr char HADAMARD_CX_SYNTAX[] = "Syntax of hadamard with cx";
    SECTION(HADAMARD_CX_SYNTAX){
        //Checking if the syntax with all the pauli gates works
        MiniQbt::QasmAsyncIntepreter intepreter;
        const char * src = 
        "// a comment               \n"
        "OPENQASM 2.0;              \n"
        "include \"qelib1.inc\";    \n"
        "qreg q[5]; creg c[5];      \n"
        "h q[1]; h q[2];            \n"
        "cx q[1], q[2];             \n"
        "measure q[1] -> c[1];      \n"
        "measure q[2] -> c[2];      \n";
        intepreter.intepret(std::string(src));
        auto res = intepreter.readClassicRegister("c");
        const bool failed = intepreter.hasErrors();
        std::stringstream ss;
        ss << "Test : " << HADAMARD_CX_SYNTAX << " Failed with errors: \n";
        while(intepreter.hasErrors()){
            ss << intepreter.getError() << "\n";
        }

        INFO(ss.str());
        REQUIRE(!failed);
    }

}