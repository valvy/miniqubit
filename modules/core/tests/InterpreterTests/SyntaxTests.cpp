#include "catch2/catch.hpp"
#include <miniqbt/interpreter/QasmAsyncInterpreter.hpp>
#include <sstream>

TEST_CASE( "Syntax tests") {
    
   

    constexpr char ENTIRE_MEASURE[] = "Entire measure";
    SECTION(ENTIRE_MEASURE){
        //Checking if the syntax with all the pauli gates works
        MiniQbt::QasmAsyncInterpreter interpreter;
        const char * src = 
        "// a comment               \n"
        "OPENQASM 2.0;              \n"
        "include \"qelib1.inc\";    \n"
        "qreg q[3]; creg c[3];      \n"
        "x q[0]; x q[1]; x q[2];    \n"
        "measure q -> c;            \n";
        interpreter.interpret(std::string(src));
        auto res = interpreter.readClassicRegister("c");
        const bool failed = interpreter.hasErrors();
        std::stringstream ss;
        ss << "Test : " << ENTIRE_MEASURE << " Failed with errors: \n";
        while(interpreter.hasErrors()){
            ss << interpreter.getError() << "\n";
        }

        INFO(ss.str());

        REQUIRE((res[0] == 1 && res[1] == 1 && res[2] == 1));
        REQUIRE(!failed);
    }

    constexpr char IN_EQUAL_MEASURE[] = "Inequal measure";
    SECTION(IN_EQUAL_MEASURE){
        //Checking if the syntax with all the pauli gates works
        MiniQbt::QasmAsyncInterpreter interpreter;
        const char * src = 
        "// a comment               \n"
        "OPENQASM 2.0;              \n"
        "include \"qelib1.inc\";    \n"
        "qreg q[4]; creg c[3];      \n"
        "x q[0]; x q[1]; x q[2];    \n"
        "measure q -> c;            \n";
        interpreter.interpret(std::string(src));
        auto res = interpreter.readClassicRegister("c");
        const bool failed = interpreter.hasErrors();
        std::stringstream ss;
        ss << "Test : " << ENTIRE_MEASURE << " Failed with errors: \n";
        INFO(ss.str());
        REQUIRE(failed);
    }


    constexpr char PAULI_SYNTAX[] = "All Pauli gates";
    SECTION(PAULI_SYNTAX){
        //Checking if the syntax with all the pauli gates works
        MiniQbt::QasmAsyncInterpreter interpreter;
        const char * src = 
        "// a comment               \n"
        "OPENQASM 2.0;              \n"
        "include \"qelib1.inc\";    \n"
        "qreg q[5]; creg c[5];      \n"
        "x q[0]; y q[1]; z q[2];    \n"
        "measure q[1] -> c[1];      \n"
        "measure q[2] -> c[2];      \n";
        interpreter.interpret(std::string(src));
        auto res = interpreter.readClassicRegister("c");
        const bool failed = interpreter.hasErrors();
        std::stringstream ss;
        ss << "Test : " << PAULI_SYNTAX << " Failed with errors: \n";
        while(interpreter.hasErrors()){
            ss << interpreter.getError() << "\n";
        }

        INFO(ss.str());
        REQUIRE(!failed);
    }

    constexpr char HADAMARD_CX_SYNTAX[] = "Syntax of hadamard with cx";
    SECTION(HADAMARD_CX_SYNTAX){
        //Checking if the syntax with all the pauli gates works
        MiniQbt::QasmAsyncInterpreter interpreter;
        const char * src = 
        "// a comment               \n"
        "OPENQASM 2.0;              \n"
        "include \"qelib1.inc\";    \n"
        "qreg q[5]; creg c[5];      \n"
        "h q[1]; h q[2];            \n"
        "cx q[1], q[2];             \n"
        "measure q[1] -> c[1];      \n"
        "measure q[2] -> c[2];      \n";
        interpreter.interpret(std::string(src));
        auto res = interpreter.readClassicRegister("c");
        const bool failed = interpreter.hasErrors();
        std::stringstream ss;
        ss << "Test : " << HADAMARD_CX_SYNTAX << " Failed with errors: \n";
        while(interpreter.hasErrors()){
            ss << interpreter.getError() << "\n";
        }

        INFO(ss.str());
        REQUIRE(!failed);
    }

}