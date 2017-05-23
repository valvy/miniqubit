#ifndef MINI_QBT_QASM_INTEPRETER_CORE_TOKEN_VISITOR_HPP
#define MINI_QBT_QASM_INTEPRETER_CORE_TOKEN_VISITOR_HPP

#include <vector>
#include <string>
#include "RegisterComposite.hpp"
#include "ClassicRegister.hpp"
#include "Tokens.hpp"


namespace MiniQbt{
    namespace Core{
        class TokenVisitor{
            private:
            bool registerDoesExist(const std::string& name) const;
            std::vector<AbstractRegister*> quantumRegisters;
            std::vector<ClassicRegister> classicRegisters;
            std::vector<GateToken> customGates;
            std::vector<std::string> errors;
            public:
            ~TokenVisitor();
            TokenVisitor();
            bool hasErrors() const;
            std::vector<std::string> getClassicRegisters() const;
            std::vector<bool> getClassicRegister(const std::string& name);
            std::string getError();
            bool doesRegisterExists(const std::string& registerName) const;
            void visit(PauliXToken& pauliGate);
            void visit(PauliYToken& pauliGate);
            void visit(PauliZToken& pauliGate);
            void visit(ClassicRegisterToken& regist);
            void visit(HadamardGateToken& hadamard);
            void visit(MeasureToken& measure);
            void visit(QuantumRegisterToken& registe);
            void visit(CNotToken& cnot);
            void visit(ErrorToken& token);
            void visit(GateToken& gate);

        };
    }
}

#endif