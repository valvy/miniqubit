#include "miniqbt/interpreter/QuantumResult.hpp"

using namespace MiniQbt;

QuantumResult::QuantumResult() {
    this->registerName = "ERROR";
}   

QuantumResult::QuantumResult(const std::string& registerName, const std::vector<bool>& data) {
    this->registerName = registerName;
    this->data = data;
}

std::string QuantumResult::getName() const {
    return this->registerName;
}
std::string QuantumResult::dataToString() const {
    return "";
}

int QuantumResult::registerSize() const {
    return this->data.size();
}

bool QuantumResult::getData(int index) const {
    if(index > this->registerSize()) {
        // todo: make a custom exception
        throw "Out of index exception";
    }
    return this->data[index];
}