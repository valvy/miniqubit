#include "catch.hpp"
#include <QuantumState.hpp>
#include <Gates.hpp>
#include <iostream>

TEST_CASE( "Single qubit algorithms") {
    constexpr size_t MINIMAL_TEST_AMOUNT = 10;
    /**
    *   Supplied algorithm from IBM
    *   https://quantumexperience.ng.bluemix.net/qstage/#/tutorial?sectionId=8443c4f713521c10b1a56a533958286b&pageIndex=2
    */
    std::random_device rd;
    std::default_random_engine generator(rd());

    constexpr char ONE_QUBIT_MES_KEY[] = "1 Qubit measurement";
    SECTION(ONE_QUBIT_MES_KEY){
        QuantumState qubit(1);
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            try{
                std::bitset<1> bitset = measure<1>(qubit, generator);
                INFO(ONE_QUBIT_MES_KEY <<" failed because answer that has been given: " << bitset << " is wrong");
                REQUIRE(bitset[0] == 0);//Answer is always 011
            } catch(const QuantumException& exp){
                FAIL(ONE_QUBIT_MES_KEY << " failed with the exception " << exp.getMessage() );
            }
        }
        
    }

    constexpr char PAULI_X_QUBIT_MES_KEY[] = "Pauli x 1 Qubit measurement";
    SECTION(PAULI_X_QUBIT_MES_KEY){
        QuantumState qubit(1);
        pauliX(0, qubit);
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            try{
                std::bitset<1> bitset = measure<1>(qubit, generator);   
                INFO(PAULI_X_QUBIT_MES_KEY <<" failed because answer that has been given: " << bitset << " is wrong");
                REQUIRE(bitset[0] == 1);
            
            } catch(const QuantumException& exp){
                FAIL(PAULI_X_QUBIT_MES_KEY << " failed with the exception " << exp.getMessage() );
            }
        }
        
    }

    constexpr char PAULI_Y_ONE_QUBIT_MEASUREMENT[] = "Pauli y 1 Qubit measurement";
    SECTION(PAULI_Y_ONE_QUBIT_MEASUREMENT){
        QuantumState qubit(1);
        pauliY(0, qubit);
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            try{
                std::bitset<1> bitset = measure<1>(qubit, generator);  
                INFO(PAULI_Y_ONE_QUBIT_MEASUREMENT  <<" failed because answer that has been given: " << bitset << " is wrong");    
                REQUIRE(bitset[0] == 0);
            } catch(const QuantumException& exp){
                FAIL(PAULI_Y_ONE_QUBIT_MEASUREMENT << " failed with the exception " << exp.getMessage() );
            }
        }
        
    }

    constexpr char PAULI_Z_ONE_QUBIT_MEASUREMENT[] = "Pauli z 1 Qubit measurement";
    SECTION(PAULI_Z_ONE_QUBIT_MEASUREMENT){
        QuantumState qubit(1);
        pauliZ(0, qubit);
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
           try{
                std::bitset<1> bitset = measure<1>(qubit, generator); 
                INFO(PAULI_Z_ONE_QUBIT_MEASUREMENT  <<" failed because answer that has been given: " << bitset << " is wrong");   
                REQUIRE(bitset[0] == 0);
            } catch(const QuantumException& exp){
                FAIL(PAULI_Z_ONE_QUBIT_MEASUREMENT << " failed with the exception " << exp.getMessage() );
            }
        }
    }


    constexpr char HADAMARD_ONE_QUBIT_MEASUREMENT[] = "Hadamard  1 Qubit measurement";
    SECTION(HADAMARD_ONE_QUBIT_MEASUREMENT){
        QuantumState qubit(1);
        hadamardGate(0, qubit);
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            try{
                std::bitset<1> bitset = measure<1>(qubit, generator); 
                INFO(HADAMARD_ONE_QUBIT_MEASUREMENT  <<" failed because answer that has been given: " << bitset << " is wrong"); 
                REQUIRE((bitset[0] == 0 || bitset[0] == 1));//Looks useless but the measure can fail
            }catch(const QuantumException& exp){
                FAIL(HADAMARD_ONE_QUBIT_MEASUREMENT << " failed with the exception " << exp.getMessage() );
            }
        }
        
    }


    constexpr char DOUBLE_HADAMARD_ONE_QUBIT_MEASUREMENT[] = "Double Hadamard  1 Qubit measurement";
    SECTION(DOUBLE_HADAMARD_ONE_QUBIT_MEASUREMENT){
        QuantumState qubit(1);
        hadamardGate(0, qubit);
        hadamardGate(0, qubit);
      
        for(size_t i = 0; i < MINIMAL_TEST_AMOUNT; i++){
            try{
                std::bitset<1> bitset = measure<1>(qubit, generator);
                INFO(DOUBLE_HADAMARD_ONE_QUBIT_MEASUREMENT  <<" failed because answer that has been given: " << bitset << " is wrong"); 
                REQUIRE(bitset[0] == 0);
            } catch(const QuantumException& exp){
                FAIL(DOUBLE_HADAMARD_ONE_QUBIT_MEASUREMENT << " failed with the exception " << exp.getMessage() );
            }
        }
        
    }
}