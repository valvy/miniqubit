#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <string>

class QuantumException{
    private:
    std::string msg;
    public: 
    QuantumException(char const* msg);
    QuantumException(const std::string& msg);
    std::string getMessage() const;
    friend std::ostream& operator<<(std::ostream& os, const QuantumException& state);
};

class InvalidInputException : public QuantumException{
    public:
    InvalidInputException(char const * msg) : QuantumException(msg){};
    InvalidInputException(const std::string& msg) : QuantumException(msg){};
};

class QuantumInfinityException : public QuantumException{
    public:
    QuantumInfinityException(char const * msg) : QuantumException(msg){};
    QuantumInfinityException(const std::string& msg) : QuantumException(msg){};
};

#endif