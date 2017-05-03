#ifndef MINI_QBT_QASM_INTEPRETER_CORE_REGISTER_COMPOSITE_HPP
#define MINI_QBT_QASM_INTEPRETER_CORE_REGISTER_COMPOSITE_HPP

#include <MiniQbtEmulator.hpp>
#include "Tokens.hpp"

namespace MiniQbt{
    namespace Core{
        class AbstractRegister {
            public:
            virtual void visit(PauliX& pauliGate) = 0;
            virtual void visit(HadamardGate& hadamard) = 0;
            virtual void visit(CNot& cnot) = 0;
            virtual std::string visit(Measure& measure) = 0;
            virtual std::string getName() const = 0;
            virtual ~AbstractRegister(){ }
        };

        template<size_t registerSize, bool strictMode = false>
        class RegisterComposite : public AbstractRegister{
            std::string name;
            MiniQbt::QuantumEmulator<registerSize, strictMode> emulator;
            MiniQbt::Core::QuantumState<registerSize> state;
            public:
            RegisterComposite(const std::string& registerName) : name(registerName){ }
            virtual ~RegisterComposite(){

            }

            virtual void visit(CNot& cnot) override{
                size_t lh = cnot.getLeftHandIndex();
                size_t rh = cnot.getRightHandIndex();
                emulator.controlledNot(lh,rh , state);
            }

            virtual void visit(PauliX& pauliGate) override{
                emulator.pauliX(pauliGate.getSize(), state);
            }

            virtual void visit(HadamardGate& hadamard) override{
                emulator.hadamardGate(hadamard.getSize(), state);
            }

            virtual std::string visit(Measure& measure) override{
                std::random_device rd;
                std::default_random_engine generator(rd());
                return emulator.measure(state, generator).to_string();
            }

            virtual std::string getName() const override{
                return this->name;
            }
        };  
    }
}



#endif