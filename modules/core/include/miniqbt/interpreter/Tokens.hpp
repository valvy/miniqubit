#ifndef MINI_QBT_QASM_INTEPRETER_CORE_TOKEN_HPP
#define MINI_QBT_QASM_INTEPRETER_CORE_TOKEN_HPP

#include <string>
#include <vector>
#include <memory>

namespace MiniQbt{
    namespace Core{

        class TokenVisitor;
        class AbstractRegister;

        class LinkedRegister{
            std::shared_ptr<AbstractRegister> link;
            int position;
            public:
            LinkedRegister(std::shared_ptr<AbstractRegister> link, int position){
                this->link = link;
                this->position = position;
            }

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
            void accept(TokenVisitor& visitor) override;
            virtual ~GateToken() { }

            
        };

        class UnkownGateToken : public Token{
            private:
            std::string name;
            std::vector<std::string> classicArguments;
            std::vector<std::string> quantumArguments;
            public:
            UnkownGateToken(const std::string& name, const std::string classicArguments, const std::string quantumArguments);
            void accept(TokenVisitor& visitor) override;
            virtual ~UnkownGateToken() { }
        };

        class MassAddToken : public Token{
            protected:
            int size = -1;
            public:
            MassAddToken(int size){
                this->size = size;
            }
            bool linkEntireToken() const { return size == -1; }
            int getSize() const { return this->size ; }
            virtual ~MassAddToken() { }
        };

        class ErrorToken : public Token {
            std::string line;
            public:
            ErrorToken(std::string line){
                this->line = line;
            }
            std::string getLine() const { return this->line; }
            void accept(TokenVisitor& visitor) override;
            virtual ~ErrorToken() { }
        };

        class IncludeToken : public Token{
            std::string incl;
            public:
            IncludeToken(std::string incl){
                this->incl = incl;
            }
            void accept(TokenVisitor& visitor) override;
            virtual ~IncludeToken() { }
        };

        class BarrierToken : public Token{
            public:
            void accept(TokenVisitor& visitor) override;
            virtual ~BarrierToken() { }
        };

        class AssemblyVersionToken : public Token{
            std::string version;
            public:
            AssemblyVersionToken(std::string version){
                this->version = version;
            }
            void accept(TokenVisitor& visitor) override;
            virtual ~AssemblyVersionToken() {}
        };

        class ClassicRegisterToken : public Token{
            std::string name;
            int size;
            public:
            ClassicRegisterToken(std::string name, int size){
                this->name = name;
                this->size = size;
            }
            std::string getName() const { return this->name; }
            int getSize() const { return this->size ; }
            void accept(TokenVisitor& visitor) override;
            virtual ~ClassicRegisterToken() { }
        };

        class QuantumRegisterToken : public Token{
            std::string name;
            int size;
            public:
            QuantumRegisterToken(std::string name, int size){
                this->name = name;
                this->size = size;
            }
            std::string getName() const { return this->name; }
            int getSize() const { return this->size ; }
            void accept(TokenVisitor& visitor) override;
            virtual ~QuantumRegisterToken() { }


        };

        class HadamardGateToken : public MassAddToken{
            std::string name;
            public:
            HadamardGateToken(std::string name, int size) : MassAddToken(size){
                this->name = name;
            }
            HadamardGateToken(std::string name) :  MassAddToken(-1) {
                this->name = name;
            }
            std::string getName() const { return this->name; }
            void accept(TokenVisitor& visitor) override;
            virtual ~HadamardGateToken() { }
        };

        class PhaseSToken : public MassAddToken{
            std::string name;
            public:
            PhaseSToken(std::string name, int size) : MassAddToken(size) {
                this->name = name;
            }
            PhaseSToken(std::string name) : MassAddToken(-1) {
                this->name = name;
            }
            std::string getName() const { return this->name; }
            void accept(TokenVisitor& visitor) override;
            virtual ~PhaseSToken() { }
        };

        class PhaseSDGToken : public MassAddToken{
            std::string name;
            public:
            PhaseSDGToken(std::string name, int size) : MassAddToken(size) {
                this->name = name;
            }
            PhaseSDGToken(std::string name) : MassAddToken(-1) {
                this->name = name;
            }
            std::string getName() const { return this->name; }
            void accept(TokenVisitor& visitor) override;
            virtual ~PhaseSDGToken() { }
        };
        

        class PhaseTToken : public MassAddToken{
            std::string name;
            public:
            PhaseTToken(std::string name, int size) : MassAddToken(size) {
                this->name = name;
            }
            PhaseTToken(std::string name) : MassAddToken(-1) {
                this->name = name;
            }
            std::string getName() const { return this->name; }
            void accept(TokenVisitor& visitor) override;
            virtual ~PhaseTToken() {} 
        };


        class PhaseTDGToken : public MassAddToken{
            std::string name;
            public:
            PhaseTDGToken(std::string name, int size) : MassAddToken(size) {
                this->name = name;
            }
            PhaseTDGToken(std::string name) : MassAddToken(-1) {
                this->name = name;
            }
            std::string getName() const { return this->name; }
            void accept(TokenVisitor& visitor) override;
            virtual ~PhaseTDGToken() { }
        };
    

        class PauliZToken : public MassAddToken{
            std::string name;
            public:
            PauliZToken(std::string name, int size) : MassAddToken(size) {
                this->name = name;
            }
            PauliZToken(std::string name) : MassAddToken(-1) {
                this->name = name;
            }
            std::string getName() const { return this->name; }
            void accept(TokenVisitor& visitor) override;
            virtual ~PauliZToken() { }

        };

        class PauliYToken : public MassAddToken{
            std::string name;
            public:
            PauliYToken(std::string name, int size) : MassAddToken(size) {
                this->name = name;
            }
            PauliYToken(std::string name) : MassAddToken(-1) {
                this->name = name;
            }
            std::string getName() const { return this->name; }
            void accept(TokenVisitor& visitor) override;
            virtual ~PauliYToken() { }

        };


        class PauliXToken : public MassAddToken{
            std::string name;
            public:
            PauliXToken(std::string name, int size) : MassAddToken(size) {
                this->name = name;
            }
            PauliXToken(std::string name) : MassAddToken(-1) {
                this->name = name;
            }
            std::string getName() const { return this->name; }
            
            void accept(TokenVisitor& visitor) override;
            virtual ~PauliXToken() { }

        };

        class MeasureToken : public Token{
            std::string quReg;
            int qubit;
            std::string classicReg;
            int bit;
            public:
            MeasureToken(std::string quReg, int qubit, std::string classicReg, int bit){
                this->quReg = quReg;
                this->qubit = qubit;
                this->classicReg = classicReg;
                this->bit = bit;
            }
            MeasureToken(std::string quReg,  std::string classicReg) {
                this->quReg = quReg;
                this->classicReg = classicReg;
                this->qubit = -1;
                this->bit = -1;
            }

            void accept(TokenVisitor& visitor) override;
            bool linkEntireToken() const { return qubit == -1; }
            int getQubitPos() const {return qubit; }
            int getClassicPos() const {return bit; }
            std::string getQureg() const { return quReg; }
            std::string getClassicReg() const {return classicReg; }
            virtual ~MeasureToken() {}
        };

        class CNotToken : public Token{
            std::string lh;
            size_t lhIndex;

            std::string rh; 
            size_t rhIndex;
            public:
            void accept(TokenVisitor& visitor) override;

            CNotToken(std::string lh, size_t lhIndex, std::string rh, size_t rhIndex){
                this->lh = lh;
                this->rh = rh;
                this->lhIndex = lhIndex;
                this->rhIndex = rhIndex;
            }
            std::string getLeftHand() const { return lh; }
            std::string getRightHand() const { return rh; }
            size_t getLeftHandIndex() const { return lhIndex; }
            size_t getRightHandIndex() const { return rhIndex; }
            virtual ~CNotToken() {}
        };
    }
}


#endif
