#ifndef MINI_QBT_RUNTIME_TOKEN_HPP
#define MINI_QBT_RUNTIME_TOKEN_HPP

#include <string>
class TokenVisitor;

class Token{
    public:
    virtual void accept(TokenVisitor& visitor) = 0;
};



class QuantumRegister : public Token{
    std::string name;
    int size;
    public:
    QuantumRegister(std::string name, int size) : name(name), size(size) {}
    std::string getName() const { return this->name; }
    int getSize() const { return this->size ; }
    virtual void accept(TokenVisitor& visitor) override;

};

class HadamardGate : public Token{
    std::string name;
    int size;
    public:
    HadamardGate(std::string name, int size) : name(name), size(size) {}
    std::string getName() const { return this->name; }
    int getSize() const { return this->size ; }
    virtual void accept(TokenVisitor& visitor) override;
};

class PauliX : public Token{
    std::string name;
    int size;
    public:
    PauliX(std::string name, int size) : name(name), size(size) {}
    std::string getName() const { return this->name; }
    int getSize() const { return this->size ; }
    virtual void accept(TokenVisitor& visitor) override;
};

class Measure : public Token{
    std::string quReg;
    int qubit;
    std::string classicReg;
    int bit;
    public:
    Measure(std::string quReg, int qubit, std::string classicReg, int bit) : quReg(quReg), qubit(qubit), classicReg(classicReg), bit(bit) {}
    virtual void accept(TokenVisitor& visitor) override;
};

#endif