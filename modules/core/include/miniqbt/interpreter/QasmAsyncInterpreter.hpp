#ifndef MINI_QBT_QASM_ASYNC_INTEPRETER_HPP
#define MINI_QBT_QASM_ASYNC_INTEPRETER_HPP

#include "TokenVisitor.hpp"
#include <vector>
#include <string>



namespace MiniQbt{
    /**
    *   Main class of handling quantum assembly.
    *   This specific interpreter allows you to interpret open quantum assembly language on the fly. 
    *   The limit is 15 qubits.
    *   @author Heiko van der Heijden
    */
    class QasmAsyncInterpreter{
        private:
        Core::TokenVisitor visitor;
        public:
        QasmAsyncInterpreter();
        /**
        *   Get's all the classic register names.
        *   @return vector, The register names.
        */
        std::vector<std::string> getRegisters() const;
        /**
        *   Get's all the quantum register names.
        *   @return vector, The register names
        */
        std::vector<std::string> getQuantumRegisters() const;
        /**
        *   Places a quantum register back into superposition.
        *   This is not possible on real quantum computers.
        *   @param quantumRegister, The registerName you want to reset
        */
        void resetSuperPosition(const std::string& quantumRegister);
        /**
        *   Start to interprets specified  open quantum assembly code.
        *   This will halt execution until it's done and it will not throw an exception with invalid quantum assembly.
        *   If invalid quantum assembly is given, you can get them with the methods, hasErrors and getError
        *   @param line,    The quantum assembly source code.
        **/
        void interpret(const std::string& line);
        /**
        *   Reads the contents of a classical register in the quantum assembly source code.
        *   This will collapse all the quantum registers linked to the specified classic register.
        *   @param registerName,    The classic register to be read.
        *   @return vector<bool>,   The result in a vector with bools
        */
        std::vector<bool> readClassicRegister(const std::string& registerName);
        /**
        *   Checks if a classic register exists.
        *   @param  registerName,   The registername you wish to check.
        *   @return bool,   returns true if the register exists.
        */
        bool doesRegisterExists(const std::string& registerName) const;

        /**
        *   Checks if during the interpretation process an error occured.
        *   @return bool,   the program had an error(s)
        */
        bool hasErrors() const;
        /**
        *   Get's the previous error and remove it from the error list in the emulator.
        *   @return string, The last error
        */
        std::string getError();
    };
}


#endif