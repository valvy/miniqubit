#ifndef MINI_QBT_QASM_INTEPRETER_CORE_TOKEN_HPP
#define MINI_QBT_QASM_INTEPRETER_CORE_TOKEN_HPP

#include <string>
#include <vector>


namespace MiniQbt{
    namespace Core{

        class TokenVisitor;
        class AbstractRegister;

        class LinkedRegister{
            std::shared_ptr<AbstractRegister> link;
            size_t position;
            public:
            LinkedRegister(std::shared_ptr<AbstractRegister> link, size_t position)
            : link(link), position(position){}

        };

        class Token{
            public:
            virtual void accept(TokenVisitor& visitor) = 0;
        };

        class GateToken : public Token{
            private:
            std::string name;
            std::string classicArguments;
            std::string quantumArguments;
            std::string instructions;
            public:
            std::string getName() const { return this->name ;}
            GateToken(const std::string& data);
            virtual void accept(TokenVisitor& visitor) override;
            
        };

        class UnkownGateToken : public Token{
            private:
            std::string name;
            std::vector<std::string> classicArguments;
            std::vector<std::string> quantumArguments;
            public:
            UnkownGateToken(const std::string& name, const std::string classicArguments, const std::string quantumArguments);
            virtual void accept(TokenVisitor& visitor) override;
        };

        class MassAddToken : public Token{
            protected:
            int size = -1;
            public:
            MassAddToken(int size) : size(size) {}
            bool linkEntireToken() const { return size == -1; }
            int getSize() const { return this->size ; }
        };

        class ErrorToken : public Token {
            std::string line;
            public:
            ErrorToken(std::string line) : line(line) {}
            std::string getLine() const { return this->line; }
            virtual void accept(TokenVisitor& visitor) override;
        };

        class IncludeToken : public Token{
            std::string incl;
            public:
            IncludeToken(std::string incl) : incl(incl) {}
            virtual void accept(TokenVisitor& visitor) override;
        };

        class AssemblyVersionToken : public Token{
            std::string version;
            public:
            AssemblyVersionToken(std::string version) : version(version) {}
            virtual void accept(TokenVisitor& visitor) override;
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

        class HadamardGateToken : public MassAddToken{
            std::string name;
            public:
            HadamardGateToken(std::string name, int size) : name(name), MassAddToken(size) {}
            HadamardGateToken(std::string name) : name(name), MassAddToken(-1) {}
            std::string getName() const { return this->name; }
            virtual void accept(TokenVisitor& visitor) override;

        };

        class PauliZToken : public MassAddToken{
            std::string name;
            public:
            PauliZToken(std::string name, int size) : name(name), MassAddToken(size) {}
            PauliZToken(std::string name) : name(name), MassAddToken(-1) {}
            std::string getName() const { return this->name; }
            virtual void accept(TokenVisitor& visitor) override;

        };

        class PauliYToken : public MassAddToken{
            std::string name;
            public:
            PauliYToken(std::string name, int size) : name(name), MassAddToken(size) {}
            PauliYToken(std::string name) : name(name), MassAddToken(-1) {}
            std::string getName() const { return this->name; }
            virtual void accept(TokenVisitor& visitor) override;

        };


        class PauliXToken : public MassAddToken{
            std::string name;
            public:
            PauliXToken(std::string name, int size) : name(name), MassAddToken(size) {}
            PauliXToken(std::string name) : name(name), MassAddToken(-1) {}
            std::string getName() const { return this->name; }
            
            virtual void accept(TokenVisitor& visitor) override;

        };

        class MeasureToken : public Token{
            std::string quReg;
            int qubit;
            std::string classicReg;
            int bit;
            public:
            MeasureToken(std::string quReg, int qubit, std::string classicReg, int bit)
             : quReg(quReg), qubit(qubit), classicReg(classicReg), bit(bit) {}
            MeasureToken(std::string quReg,  std::string classicReg) 
             : quReg(quReg), qubit(-1), classicReg(classicReg), bit(-1) {}

            virtual void accept(TokenVisitor& visitor) override;
            bool linkEntireToken() const { return qubit == -1; }
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