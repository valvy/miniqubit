#include "catch2/catch.hpp"
#include <miniqbt/interpreter/QasmAsyncInterpreter.hpp>

TEST_CASE( "Asyncronous coding tests") {
    
    constexpr char ONE_PAULI[] = "One PauliX test";
    SECTION(ONE_PAULI){
        MiniQbt::QasmAsyncInterpreter interpreter;
        interpreter.interpret("qreg q[5];");
        interpreter.interpret("creg c[5];");
        interpreter.interpret("x q[2];");
        interpreter.interpret("measure q[0] -> c[0];");
        interpreter.interpret("measure q[1] -> c[1];");
        interpreter.interpret("measure q[2] -> c[2];");
        interpreter.interpret("measure q[3] -> c[3];");
        interpreter.interpret("measure q[4] -> c[4];");
        auto res = interpreter.readClassicResult("c");

        REQUIRE(res.getData(2) == 1);
        REQUIRE(!interpreter.hasErrors());
    }

    constexpr char ERROR_LINE_PROGRAM[] = "Error in program"; 
    SECTION(ERROR_LINE_PROGRAM){
        MiniQbt::QasmAsyncInterpreter interpreter;
        interpreter.interpret("qreg q[5];");
        interpreter.interpret("creg c[5];");
        interpreter.interpret("ERROR;");
        interpreter.interpret("measure q[0] -> c[0];");
        auto res = interpreter.readClassicResult("c");
        REQUIRE(interpreter.hasErrors());
    }

    constexpr char MISSING_SEMICOLON[] = "missing semicolon"; 
    SECTION(MISSING_SEMICOLON){
        MiniQbt::QasmAsyncInterpreter interpreter;
        interpreter.interpret("qreg q[5];");
        interpreter.interpret("creg c[5];");
        interpreter.interpret("ERROR");
        interpreter.interpret("measure q[0] -> c[0];");
        auto res = interpreter.readClassicResult("c");
        REQUIRE(interpreter.hasErrors());
    }


    constexpr char DOUBLE_EXPRESSIONS[] = "double expression"; 
    SECTION(DOUBLE_EXPRESSIONS){
        MiniQbt::QasmAsyncInterpreter interpreter;
        interpreter.interpret("qreg q[5]; creg c[5];");
        interpreter.interpret("x q[2];");
        interpreter.interpret("measure q[2] -> c[0];");
        auto res = interpreter.readClassicResult("c");
    //    REQUIRE(res[0] == 1);
        REQUIRE(!interpreter.hasErrors());
    }

    constexpr char EMPTY_EXPRESSION[] = "Empty expression"; 
    SECTION(EMPTY_EXPRESSION){
        MiniQbt::QasmAsyncInterpreter interpreter;
        interpreter.interpret("qreg q[5]; creg c[5];");
        interpreter.interpret(";");//error
        REQUIRE(interpreter.hasErrors());
       
    }

    constexpr char EMPTY_EXPRESSION_WITH_SPACES[] = "Empty expression with spaces"; 
    SECTION(EMPTY_EXPRESSION_WITH_SPACES){
        MiniQbt::QasmAsyncInterpreter interpreter;
        interpreter.interpret("qreg q[5]; creg c[5];");
        interpreter.interpret("; ; ;;"); //annoying thing
        interpreter.interpret("x q[2];");
        interpreter.interpret("measure q[0] -> c[0];");
        auto res = interpreter.readClassicResult("c");
        REQUIRE(interpreter.hasErrors());
    }

    constexpr char EXPRESSION_WITH_NLINE[] = "Expression with new line"; 
    SECTION(EXPRESSION_WITH_NLINE){
        MiniQbt::QasmAsyncInterpreter interpreter;
        interpreter.interpret("qreg q[5]; \n\n creg c[5];");
        interpreter.interpret("x q[2];");
        interpreter.interpret("measure q[0] -> c[0];");
        auto res = interpreter.readClassicResult("c");
        REQUIRE(!interpreter.hasErrors());
    }
    constexpr char EXPRESSION_WITH_ONLY_NLINE[] = "Expression with only a new line"; 
    SECTION(EXPRESSION_WITH_ONLY_NLINE){
        MiniQbt::QasmAsyncInterpreter interpreter;
        interpreter.interpret("qreg q[5];  creg c[5];");
        interpreter.interpret("\n");
        interpreter.interpret("measure q[0] -> c[0];");
        auto res = interpreter.readClassicResult("c");
        REQUIRE(!interpreter.hasErrors());
    }
    constexpr char EXPRESSION_WITH_MORE_NLINE[] = "Expression with only and more then a new line"; 
    SECTION(EXPRESSION_WITH_MORE_NLINE){
        MiniQbt::QasmAsyncInterpreter interpreter;
        interpreter.interpret("qreg q[5];  creg c[5];");
        interpreter.interpret("\n\n");
        interpreter.interpret("measure q[0] -> c[0];");
        auto res = interpreter.readClassicResult("c");
        REQUIRE(!interpreter.hasErrors());
    }

    constexpr char MULTI_LINE_EXPRESSION[] = "Expression with semicolon on new line"; 
    SECTION(MULTI_LINE_EXPRESSION){
        MiniQbt::QasmAsyncInterpreter interpreter;
        interpreter.interpret("qreg q[5] \n ;  creg c[5];");
        interpreter.interpret("measure q[0] -> c[0];");
        auto res = interpreter.readClassicResult("c");
        REQUIRE(!interpreter.hasErrors());
    }

    constexpr char ONE_BIG_EXPRESSION[] = "Everything on one line"; 
    SECTION(ONE_BIG_EXPRESSION){
        MiniQbt::QasmAsyncInterpreter interpreter;
        const char* src = 
        "qreg q[5]; creg c[5];  \n"
        "x q[0]; x q[1];        \n"
        "measure q[0] -> c[0];  \n"
        "measure q[1] -> c[1];  \n";
    
        interpreter.interpret(std::string(src));
        auto res = interpreter.readClassicResult("c");

        REQUIRE(!interpreter.hasErrors());
        REQUIRE(res.getData(4) == 1);
        REQUIRE(res.getData(3) == 1);
        REQUIRE(res.getData(2) == 0);
    }
    
    constexpr char ONE_CNOT[] = "One CNOT test";
    SECTION(ONE_CNOT){
        MiniQbt::QasmAsyncInterpreter interpreter;
        interpreter.interpret("qreg q[5];");
        interpreter.interpret("creg c[5];");
        interpreter.interpret("cx q[1],q[2];");
        interpreter.interpret("measure q[0] -> c[0];");
        interpreter.interpret("measure q[1] -> c[1];");
        interpreter.interpret("measure q[2] -> c[2];");
        interpreter.interpret("measure q[3] -> c[3];");
        interpreter.interpret("measure q[4] -> c[4];");
        auto res = interpreter.readClassicResult("c");

      //  REQUIRE(res[2] == 1);
        REQUIRE(!interpreter.hasErrors());
    }

    constexpr char COMMENT_TEST[] = "Comment tests";
    SECTION(COMMENT_TEST){
        MiniQbt::QasmAsyncInterpreter interpreter;
        interpreter.interpret("qreg q[5]; //this is a comment;; \n //this is also a comment");
        interpreter.interpret("creg c[5];");
        interpreter.interpret("measure q[0] -> c[0];");
        auto res = interpreter.readClassicResult("c");

      //  REQUIRE(res[2] == 1);
        REQUIRE(!interpreter.hasErrors());
    }

}
