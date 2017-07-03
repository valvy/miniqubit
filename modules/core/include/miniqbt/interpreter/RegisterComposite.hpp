#ifndef MINI_QBT_QASM_INTEPRETER_CORE_REGISTER_COMPOSITE_HPP
#define MINI_QBT_QASM_INTEPRETER_CORE_REGISTER_COMPOSITE_HPP

#include "miniqbt/emulator/MiniQbtEmulator.hpp"
#include "Tokens.hpp"
#include <iostream>

namespace MiniQbt{
    namespace Core{
        /**
        *   Generic class for handling different sizes of quantum registers.
        *   @author Heiko van der Heijden
        */
        class AbstractRegister {
            public:
            virtual void visit(PauliXToken& pauliGate) = 0;
            virtual void visit(PauliYToken& pauliGate) = 0;
            virtual void visit(PauliZToken& pauliGate) = 0;
            virtual void visit(PhaseSToken& phaseSToken) = 0;
            virtual void visit(PhaseSDGToken& phaseSDGToken) = 0;
            virtual void visit(PhaseTToken& phaseTToken) = 0;
            virtual void visit(PhaseTDGToken& phaseTDGToken) = 0;
            virtual void visit(HadamardGateToken& hadamard) = 0;
            virtual void visit(CNotToken& cnot) = 0;
            virtual void resetSuperPosition() = 0;
            virtual int getSize() const = 0;
            virtual bool operator[](int pos) const = 0;
            virtual void collapse() = 0;
            virtual std::string getName() const = 0;
            virtual ~AbstractRegister(){ }
        };

        template<int registerSize, bool strictMode = false>
        class RegisterComposite : public AbstractRegister{
            std::string name;
            MiniQbt::QuantumEmulator<registerSize, strictMode> emulator;
            MiniQbt::Core::QuantumState<registerSize> state;
            std::bitset<registerSize> collapsedResult;
            bool collapsed = false;
            public:
            RegisterComposite(const std::string& registerName) : name(registerName){ }
            virtual ~RegisterComposite(){

            }
            
            virtual int getSize() const override{
                return registerSize;
            }

            virtual bool operator[](int pos) const override{
                return collapsedResult[pos];
            }

            virtual void collapse() override{
                if(!collapsed){
                    std::random_device rd;
                    std::default_random_engine generator(rd());
                    this->collapsedResult = emulator.measure(state, generator);
                    collapsed = true;
                   // std::cout << collapsedResult << "\n";
                }
            }
            
            virtual void resetSuperPosition() override {
                collapsed = false;
            }

            virtual void visit(PhaseSToken& phaseSToken) override{
                if(phaseSToken.linkEntireToken()){
                    for(int i = 0; i < registerSize; i++){
                        emulator.phaseS(i,state);
                    }
                } else {
                    emulator.phaseS(phaseSToken.getSize(), state);
                }
            }

            virtual void visit(PhaseSDGToken& phaseSDGToken) override{
                if(phaseSDGToken.linkEntireToken()){
                    for(int i = 0; i < registerSize; i++){
                        emulator.phaseSDG(i,state);
                    }
                } else {
                    emulator.phaseSDG(phaseSDGToken.getSize(), state);
                }
            }

            virtual void visit(PhaseTToken& phaseTToken) override{
                if(phaseTToken.linkEntireToken()){
                    for(int i = 0; i < registerSize; i++){
                        emulator.phaseT(i,state);
                    }
                } else {
                    emulator.phaseT(phaseTToken.getSize(), state);
                }
            }

            virtual void visit(PhaseTDGToken& phaseTDGToken) override{
                if(phaseTDGToken.linkEntireToken()){
                    for(int i = 0; i < registerSize; i++){
                        emulator.phaseTDG(i,state);
                    }
                } else {
                    emulator.phaseTDG(phaseTDGToken.getSize(), state);
                }
            }

            virtual void visit(CNotToken& cnot) override{
                int lh = cnot.getLeftHandIndex();
                int rh = cnot.getRightHandIndex();
                emulator.controlledNot(lh,rh , state);
            }

            virtual void visit(PauliXToken& pauliGate) override{
                if(pauliGate.linkEntireToken()){
                    for(int i = 0; i < registerSize; i++){
                        emulator.pauliX(i, state);
                    }
                } else {
                    emulator.pauliX(pauliGate.getSize(), state);
                }

             
            }

            virtual void visit(PauliYToken& pauliGate) override{
                if(pauliGate.linkEntireToken()){
                    for(int i = 0; i < registerSize; i++){
                        emulator.pauliY(i, state);
                    }
                } else {
                    emulator.pauliY(pauliGate.getSize(), state);
                }
            }

            virtual void visit(PauliZToken& pauliGate) override{
                if(pauliGate.linkEntireToken()){
                    for(int i = 0; i < registerSize; i++){
                        emulator.pauliZ(i, state);
                    }
                } else {
                    emulator.pauliZ(pauliGate.getSize(), state);
                }
              
            }

            virtual void visit(HadamardGateToken& hadamard) override{
                if(hadamard.linkEntireToken()){
                    for(int i = 0; i < registerSize; i++){
                        emulator.hadamardGate(i, state);
                    }
                } else {
                    emulator.hadamardGate(hadamard.getSize(), state);
                }
            }

  

            virtual std::string getName() const override{
                return this->name;
            }
        };  
    }
}



#endif