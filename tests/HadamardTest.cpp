
#include "catch.hpp"
#include <MiniQbt.hpp>


TEST_CASE( "hadamard with Controlled not") {
    constexpr size_t MINIMAL_TEST_AMOUNT = 100;
    std::random_device rd;
    std::default_random_engine generator(rd());
    using namespace MiniQbt;
    constexpr char FIRST_QUBIT_APPLIED_HADAMARD[] = "first qubit applied hadamard";
    SECTION(FIRST_QUBIT_APPLIED_HADAMARD){
        Quantum2 emulator;
        auto ent = emulator.generateRegister();
        emulator.hadamardGate(0,ent);
        emulator.controlledNot(0,1,ent);
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            try{
                std::bitset<2> bitset = emulator.measure(ent, generator);
                INFO(FIRST_QUBIT_APPLIED_HADAMARD << " failed because answer that has been given: " << bitset << " is wrong");
                REQUIRE(bitset[0] == bitset[1]);
            } catch(const QuantumException& exp){
                 FAIL(FIRST_QUBIT_APPLIED_HADAMARD << " failed with the exception " << exp.getMessage() );
            }
        }
    }
    
    constexpr char SECOND_QUBIT_APPLIED_HADAMARD_KEY[] = "Second qubit applied hadamard";
    SECTION(SECOND_QUBIT_APPLIED_HADAMARD_KEY){
        Quantum5 emulator;
        auto ent = emulator.generateRegister();
        emulator.hadamardGate(1, ent);
        emulator.controlledNot(0,1, ent);
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            try{
                std::bitset<5> bitset = emulator.measure(ent, generator);
                INFO(SECOND_QUBIT_APPLIED_HADAMARD_KEY << " failed because answer that has been given: " << bitset << " is wrong");
                REQUIRE(bitset[4] == 0); //other bit can be 1 :)
            } catch(const QuantumException& exp){
                 FAIL(SECOND_QUBIT_APPLIED_HADAMARD_KEY << " failed with the exception " << exp.getMessage() );
            }
        }
    }
    
    constexpr char QUADRUPLE_HADAMARD_WITH_CNOT[] = "Quadruple hadamard with CNOT";
    SECTION(QUADRUPLE_HADAMARD_WITH_CNOT){
        Quantum2 emulator;
        auto ent = emulator.generateRegister();
        emulator.hadamardGate(0, ent);
        emulator.hadamardGate(1, ent);
        emulator.controlledNot(0,1, ent);
        emulator.hadamardGate(0, ent);
        emulator.hadamardGate(1, ent); 
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            try{
                std::bitset<2> bitset = emulator.measure(ent, generator);
                INFO(QUADRUPLE_HADAMARD_WITH_CNOT << " failed because answer that has been given: " << bitset << " is wrong");
                REQUIRE(bitset[0] == 0);
                REQUIRE(bitset[1] == 0);
            } catch(const QuantumException& exp){
                 FAIL(QUADRUPLE_HADAMARD_WITH_CNOT << " failed with the exception " << exp.getMessage() );
            }
        }
    }
    
    constexpr char PAULI_X_AFTER_HADAMARD_AND_CONTROLLED_NOT_GATE[] = "Pauli x after hadamard and controlled not gate";
    SECTION(PAULI_X_AFTER_HADAMARD_AND_CONTROLLED_NOT_GATE){
        Quantum5 emulator;
        auto ent = emulator.generateRegister();
        emulator.controlledNot(0,1, ent);
        emulator.pauliX(0, ent);
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            try{
                std::bitset<5> bitset = emulator.measure(ent, generator);
                INFO(PAULI_X_AFTER_HADAMARD_AND_CONTROLLED_NOT_GATE << " failed because answer that has been given: " << bitset << " is wrong");
                REQUIRE(bitset[5] != bitset[4]);//Bits are opposite of each other
             } catch(const QuantumException& exp){
                 FAIL(PAULI_X_AFTER_HADAMARD_AND_CONTROLLED_NOT_GATE << " failed with the exception " << exp.getMessage() );
            }
        }
    }
    
    constexpr char QUADRUPLE_HADAMARD_WITH_IN_OTHER_ORDER_CNOT[] = "Quadruple hadamard with in other order CNOT";
    SECTION(QUADRUPLE_HADAMARD_WITH_IN_OTHER_ORDER_CNOT){
        Quantum2 emulator;
        auto ent = emulator.generateRegister();       
        emulator.hadamardGate(0, ent); 
        emulator.hadamardGate(1, ent); 
        emulator.controlledNot(0,1, ent);
        emulator.hadamardGate(1, ent);
        emulator.hadamardGate(0, ent); 
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            try{
                std::bitset<2> bitset = emulator.measure(ent, generator);
                INFO(QUADRUPLE_HADAMARD_WITH_IN_OTHER_ORDER_CNOT << " failed because answer that has been given: " << bitset << " is wrong");
                REQUIRE(bitset[0] == 0);
                REQUIRE(bitset[1] == 0);
            } catch(const QuantumException& exp){
                 FAIL(QUADRUPLE_HADAMARD_WITH_IN_OTHER_ORDER_CNOT << "failed with the exception " << exp.getMessage() );
            }
        }
    }
    
    constexpr char THREE_QUBITS_INCLUDING_HADAMARD_AND_PAULI[] = "Three qubits including hadamard and Pauli";
    SECTION(THREE_QUBITS_INCLUDING_HADAMARD_AND_PAULI){
        Quantum3 emulator;
        auto ent = emulator.generateRegister();   
        emulator.hadamardGate(0,ent);
        emulator.hadamardGate(1,ent);
        emulator.hadamardGate(2,ent);
        emulator.controlledNot(0,1, ent);
        emulator.pauliX(0, ent);
        emulator.hadamardGate(1,ent);
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            try{
                std::bitset<3> bitset = emulator.measure(ent, generator);
                INFO(THREE_QUBITS_INCLUDING_HADAMARD_AND_PAULI<< " failed because answer that has been given: " << bitset << " is wrong");
                REQUIRE(bitset[1] == 0);//middle in this algorithm is always zero
            } catch(const QuantumException& exp){
                 FAIL(THREE_QUBITS_INCLUDING_HADAMARD_AND_PAULI<<" failed with the exception " << exp.getMessage() );
            }
        }
    }
}

