#ifndef MINI_QBT_QASM_ASYNC_INTEPRETER_HPP
#define MINI_QBT_QASM_ASYNC_INTEPRETER_HPP

#include "TokenVisitor.hpp"
#include <vector>
#include <string>

namespace MiniQbt{
    class QasmAsyncIntepreter{
        private:
        Core::TokenVisitor visitor;
        public:
        QasmAsyncIntepreter();
        std::vector<std::string> getRegisters() const;
        std::vector<std::string> getQuantumRegisters() const;
        void resetSuperPosition(const std::string& quantumRegister);
        void intepret(const std::string& line);
        std::vector<bool> readClassicRegister(const std::string& registerName);
        bool doesRegisterExists(const std::string& registerName) const;
        bool hasErrors() const;
        std::string getError();
    };
}



#endif