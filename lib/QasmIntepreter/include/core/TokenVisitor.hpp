#ifndef MINI_QBT_QASM_INTEPRETER_CORE_TOKEN_VISITOR_HPP
#define MINI_QBT_QASM_INTEPRETER_CORE_TOKEN_VISITOR_HPP

#include <vector>
#include <string>
#include "RegisterComposite.hpp"
#include "Tokens.hpp"

namespace MiniQbt{
    namespace Core{
        class TokenVisitor{
            private:
            bool registerDoesExist(const std::string& name) const;
            std::vector<AbstractRegister*> registers;
            std::vector<std::string> errors;
            public:
            TokenVisitor();
            bool hasErrors() const;
            std::string getError();
            void visit(PauliX& pauliGate);
            void visit(HadamardGate& hadamard);
            void visit(Measure& measure);
            void visit(QuantumRegister& registe);
            void visit(CNot& cnot);
            void visit(ErrorToken& token);

        };
    }
}

#endif