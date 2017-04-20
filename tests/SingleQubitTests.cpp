#include "catch.hpp"
#include <MiniQbt.hpp>
//#include <iostream>

TEST_CASE( "Single qubit algorithms") {
    constexpr size_t MINIMAL_TEST_AMOUNT = 10;
    using namespace MiniQbt;
    std::random_device rd;
    std::default_random_engine generator(rd());

    constexpr char ONE_QUBIT_MES_KEY[] = "1 Qubit measurement";
    SECTION(ONE_QUBIT_MES_KEY){
        //Quantum1 qubit(1);
        Quantum1 emulator;
        auto qubit = emulator.generateRegister();
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            try{
                std::bitset<1> bitset = emulator.measure(qubit, generator);
                INFO(ONE_QUBIT_MES_KEY <<" failed because answer that has been given: " << bitset << " is wrong");
                REQUIRE(bitset[0] == 0);//Answer is always 011
            } catch(const QuantumException& exp){
                FAIL(ONE_QUBIT_MES_KEY << " failed with the exception " << exp.getMessage() );
            }
        }
        
    }
    
    constexpr char PAULI_X_QUBIT_MES_KEY[] = "Pauli x 1 Qubit measurement";
    SECTION(PAULI_X_QUBIT_MES_KEY){
        Quantum1 emulator;//QuantumState qubit(1);
        auto qubit = emulator.generateRegister();
        emulator.pauliX(0, qubit);
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            try{
                std::bitset<1> bitset = emulator.measure(qubit, generator);   
                INFO(PAULI_X_QUBIT_MES_KEY <<" failed because answer that has been given: " << bitset << " is wrong");
                REQUIRE(bitset[0] == 1);
            
            } catch(const QuantumException& exp){
                FAIL(PAULI_X_QUBIT_MES_KEY << " failed with the exception " << exp.getMessage() );
            }
        }
        
    }
    
    constexpr char PAULI_Y_ONE_QUBIT_MEASUREMENT[] = "Pauli y 1 Qubit measurement";
    SECTION(PAULI_Y_ONE_QUBIT_MEASUREMENT){
        Quantum1 emulator;
        auto qubit = emulator.generateRegister();
        emulator.pauliY(0, qubit);
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            try{
                std::bitset<1> bitset = emulator.measure(qubit, generator);  
                INFO(PAULI_Y_ONE_QUBIT_MEASUREMENT  <<" failed because answer that has been given: " << bitset << " is wrong");    
                REQUIRE(bitset[0] == 0);
            } catch(const QuantumException& exp){
                FAIL(PAULI_Y_ONE_QUBIT_MEASUREMENT << " failed with the exception " << exp.getMessage() );
            }
        }
        
    }
    
    constexpr char PAULI_Z_ONE_QUBIT_MEASUREMENT[] = "Pauli z 1 Qubit measurement";
    SECTION(PAULI_Z_ONE_QUBIT_MEASUREMENT){
        Quantum1 emulator;
        auto qubit = emulator.generateRegister();
        emulator.pauliZ(0, qubit);
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
           try{
                std::bitset<1> bitset = emulator.measure(qubit, generator); 
                INFO(PAULI_Z_ONE_QUBIT_MEASUREMENT  <<" failed because answer that has been given: " << bitset << " is wrong");   
                REQUIRE(bitset[0] == 0);
            } catch(const QuantumException& exp){
                FAIL(PAULI_Z_ONE_QUBIT_MEASUREMENT << " failed with the exception " << exp.getMessage() );
            }
        }
    }
    

    constexpr char HADAMARD_ONE_QUBIT_MEASUREMENT[] = "Hadamard  1 Qubit measurement";
    SECTION(HADAMARD_ONE_QUBIT_MEASUREMENT){
        Quantum1 emulator;
        auto qubit = emulator.generateRegister();
        
        emulator.hadamardGate(0, qubit);
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            try{
                std::bitset<1> bitset = emulator.measure(qubit, generator); 
                INFO(HADAMARD_ONE_QUBIT_MEASUREMENT  <<" failed because answer that has been given: " << bitset << " is wrong"); 
                REQUIRE((bitset[0] == 0 || bitset[0] == 1));//Looks useless but the measure can fail
            }catch(const QuantumException& exp){
                FAIL(HADAMARD_ONE_QUBIT_MEASUREMENT << " failed with the exception " << exp.getMessage() );
            }
        }
        
    }

    
    constexpr char DOUBLE_HADAMARD_ONE_QUBIT_MEASUREMENT[] = "Double Hadamard  1 Qubit measurement";
    SECTION(DOUBLE_HADAMARD_ONE_QUBIT_MEASUREMENT){
        Quantum1 emulator;
        auto qubit = emulator.generateRegister();
        emulator.hadamardGate(0, qubit);
        emulator.hadamardGate(0, qubit);
      
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            try{
                std::bitset<1> bitset =  emulator.measure(qubit, generator);
                INFO(DOUBLE_HADAMARD_ONE_QUBIT_MEASUREMENT  <<" failed because answer that has been given: " << bitset << " is wrong"); 
                REQUIRE(bitset[0] == 0);
            } catch(const QuantumException& exp){
                FAIL(DOUBLE_HADAMARD_ONE_QUBIT_MEASUREMENT << " failed with the exception " << exp.getMessage() );
            }
        }
        
    }
}