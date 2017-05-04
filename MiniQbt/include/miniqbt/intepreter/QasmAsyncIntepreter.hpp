#ifndef MINI_QBT_QASM_ASYNC_INTEPRETER_HPP
#define MINI_QBT_QASM_ASYNC_INTEPRETER_HPP

#include "TokenVisitor.hpp"
#include <vector>

namespace MiniQbt{
    class QasmAsyncIntepreter{
        private:
        Core::TokenVisitor visitor;
        public:
        QasmAsyncIntepreter();
        void intepret(const std::string& line);
        std::vector<bool> readClassicRegister(const std::string& registerName);
        void stop();
        bool hasErrors() const;
        std::string getError();
    };
}



#endif