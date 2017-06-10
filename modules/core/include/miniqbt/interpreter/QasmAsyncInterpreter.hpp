#ifndef MINI_QBT_QASM_ASYNC_INTEPRETER_HPP
#define MINI_QBT_QASM_ASYNC_INTEPRETER_HPP

#include "TokenVisitor.hpp"
#include <vector>
#include <string>

namespace MiniQbt{
    class QasmAsyncInterpreter{
        private:
        Core::TokenVisitor visitor;
        public:
        QasmAsyncInterpreter();
        std::vector<std::string> getRegisters() const;
        std::vector<std::string> getQuantumRegisters() const;
        void resetSuperPosition(const std::string& quantumRegister);
        void interpret(const std::string& line);
        std::vector<bool> readClassicRegister(const std::string& registerName);
        bool doesRegisterExists(const std::string& registerName) const;
        bool hasErrors() const;
        std::string getError();
    };
}



#endif