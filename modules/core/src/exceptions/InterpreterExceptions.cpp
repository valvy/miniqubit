#include "miniqbt/interpreter/exceptions/InterpreterExceptions.hpp"


using namespace MiniQbt;

InterpreterOutOfIndexException::InterpreterOutOfIndexException() : QuantumException ("Interpreter is out of index" ) { }
