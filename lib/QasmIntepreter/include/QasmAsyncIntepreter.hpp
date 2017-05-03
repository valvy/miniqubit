#ifndef MINI_QBT_QASM_ASYNC_INTEPRETER_HPP
#define MINI_QBT_QASM_ASYNC_INTEPRETER_HPP

#include "core/TokenVisitor.hpp"

namespace MiniQbt{
    class QasmAsyncIntepreter{
        private:
        Core::TokenVisitor visitor;
        public:
        QasmAsyncIntepreter();
        void intepret(const std::string& line);
        void stop();
        bool hasErrors() const;
        std::string getError();
    };
}



#endif