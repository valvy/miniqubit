#ifndef MINI_QBT_QASM_INTEPRETER_CORE_REGISTER_COMPOSITE_HPP
#define MINI_QBT_QASM_INTEPRETER_CORE_REGISTER_COMPOSITE_HPP

#include "miniqbt/emulator/MiniQbtEmulator.hpp"
#include "Tokens.hpp"
#include <iostream>

namespace MiniQbt{
    namespace Core{
        class AbstractRegister {
            public:
            virtual void visit(PauliXToken& pauliGate) = 0;
            virtual void visit(HadamardGateToken& hadamard) = 0;
            virtual void visit(CNotToken& cnot) = 0;
            virtual bool operator[](int pos) const = 0;
            virtual void collapse() = 0;
            virtual std::string getName() const = 0;
            virtual ~AbstractRegister(){ }
        };

        template<size_t registerSize, bool strictMode = false>
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

            virtual void visit(CNotToken& cnot) override{
                size_t lh = cnot.getLeftHandIndex();
                size_t rh = cnot.getRightHandIndex();
                emulator.controlledNot(lh,rh , state);
            }

            virtual void visit(PauliXToken& pauliGate) override{
                emulator.pauliX(pauliGate.getSize(), state);
            }

            virtual void visit(HadamardGateToken& hadamard) override{
                emulator.hadamardGate(hadamard.getSize(), state);
            }

  

            virtual std::string getName() const override{
                return this->name;
            }
        };  
    }
}



#endif