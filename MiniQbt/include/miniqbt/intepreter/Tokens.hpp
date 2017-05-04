#ifndef MINI_QBT_QASM_INTEPRETER_CORE_TOKEN_HPP
#define MINI_QBT_QASM_INTEPRETER_CORE_TOKEN_HPP

#include <string>



namespace MiniQbt{
    namespace Core{

        class TokenVisitor;

        class Token{
            public:
            virtual void accept(TokenVisitor& visitor) = 0;
        };

        class ErrorToken : public Token {
            std::string line;
            public:
            ErrorToken(std::string line) : line(line) {}
            std::string getLine() const { return this->line; }
            virtual void accept(TokenVisitor& visitor) override;
        };

        class CommentToken : public Token{ 
            public:
            virtual void accept(TokenVisitor& visitor) override {}
        };

        class ClassicRegisterToken : public Token{
            std::string name;
            int size;
            public:
            ClassicRegisterToken(std::string name, int size) : name(name), size(size) {}
            std::string getName() const { return this->name; }
            int getSize() const { return this->size ; }
            virtual void accept(TokenVisitor& visitor) override;
        };

        class QuantumRegisterToken : public Token{
            std::string name;
            int size;
            public:
            QuantumRegisterToken(std::string name, int size) : name(name), size(size) {}
            std::string getName() const { return this->name; }
            int getSize() const { return this->size ; }
            virtual void accept(TokenVisitor& visitor) override;


        };

        class HadamardGateToken : public Token{
            std::string name;
            int size;
            public:
            HadamardGateToken(std::string name, int size) : name(name), size(size) {}
            std::string getName() const { return this->name; }
            int getSize() const { return this->size ; }
            virtual void accept(TokenVisitor& visitor) override;

        };

        class PauliXToken : public Token{
            std::string name;
            int size;
            public:
            PauliXToken(std::string name, int size) : name(name), size(size) {}
            std::string getName() const { return this->name; }
            int getSize() const { return this->size ; }
            virtual void accept(TokenVisitor& visitor) override;

        };

        class MeasureToken : public Token{
            std::string quReg;
            int qubit;
            std::string classicReg;
            int bit;
            public:
            MeasureToken(std::string quReg, int qubit, std::string classicReg, int bit) : quReg(quReg), qubit(qubit), classicReg(classicReg), bit(bit) {}
            virtual void accept(TokenVisitor& visitor) override;
            int getQubitPos() const {return qubit; }
            int getClassicPos() const {return bit; }
            std::string getQureg() const { return quReg; }
            std::string getClassicReg() const {return classicReg; }
        };

        class CNotToken : public Token{
            std::string lh;
            size_t lhIndex;

            std::string rh; 
            size_t rhIndex;
            public:
            virtual void accept(TokenVisitor& visitor) override;

            CNotToken(std::string lh, size_t lhIndex, std::string rh, size_t rhIndex) :
            lh(lh), lhIndex(lhIndex), rh(rh), rhIndex(rhIndex){ }
            std::string getLeftHand() const { return lh; }
            std::string getRightHand() const { return rh; }
            size_t getLeftHandIndex() const { return lhIndex; }
            size_t getRightHandIndex() const { return rhIndex; }
        };
    }
}


#endif