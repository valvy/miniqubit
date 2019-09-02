#ifndef MINI_QBT_QASM_INTEPRETER_CORE_QUANTUM_RESULT_HPP
#define MINI_QBT_QASM_INTEPRETER_CORE_QUANTUM_RESULT_HPP
#include <string>
#include <vector>
namespace MiniQbt{
    class QuantumResult {
        private:
        std::string registerName;
        std::vector<bool> data;
        public:
        QuantumResult();
        QuantumResult(const std::string& registerName, const std::vector<bool>& data);
        std::string getName() const;
        std::string dataToString() const;
        int registerSize() const;
        bool getData(int index) const;
    };
    
}

#endif
