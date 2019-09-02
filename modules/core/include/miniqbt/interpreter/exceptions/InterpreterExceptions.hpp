#ifndef MINI_QBT_EXCEPTIONS_INTERPRETER_EXCEPTION_HPP
#define MINI_QBT_EXCEPTIONS_INTERPRETER_EXCEPTION_HPP
#include "miniqbt/emulator/Exceptions.hpp"

namespace MiniQbt{
    class InterpreterOutOfIndexException : public QuantumException {
        public:
        InterpreterOutOfIndexException();
    };
}

#endif