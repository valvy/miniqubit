#include <MiniQbt.hpp>
#include "Utils.hpp"
#include <regex>
#include <utility>
#include <iostream>
template<size_t size>
void showResult( MiniQbt::Core::QuantumState<size>& reg ,  MiniQbt::QuantumEmulator<size>& emulator){
    std::vector<std::pair<std::bitset<size>, size_t>> outcomes;
    std::random_device rd;
    std::default_random_engine generator(rd());
    for(size_t i = 0; i < 10000; i++){
        std::bitset<size> outcom =  emulator.measure(reg, generator);
        bool inList = false;
        for(auto& pair : outcomes){
            if(pair.first == outcom){
                pair.second++;
                inList = true;
            }
        }
        if(!inList){
            outcomes.push_back(std::make_pair(outcom, 1));
        }
        //std::cout << measure<size>(ent, generator) << "\n";
    }
    //std::cout << ent.getState() << "\n";
    std::cout << "Result \t | times found \n";
    std::cout << "-------------------------------\n";
    for(const auto& result : outcomes){
        std::cout << result.first << "\t | " << result.second << "\n";
    }
}

constexpr size_t size = 3;

void multiSystemTest(){
    using namespace MiniQbt;
    QuantumEmulator<5> emulator;
    auto state = emulator.generateRegister();
    emulator.pauliX(0, state);
    emulator.hadamardGate(0,state);
    std::random_device rd;
    std::default_random_engine generator(rd());
    showResult<5>(state, emulator);


       /* QuantumState<5> ent;

        phaseS(0,ent);
        pauliX(1,ent);
        pauliX(2, ent);
        pauliX(4,ent);

        pauliX(1,ent);
        pauliX(2,ent);
        pauliX(3,ent);
        pauliX(4,ent);

        cnotGate(3,2, ent);
        cnotGate(2,3, ent);
        cnotGate(3,2, ent);

        cnotGate(2,1, ent);
        cnotGate(1,2, ent);
        cnotGate(2,1, ent);

        cnotGate(4,1, ent);
        cnotGate(1,4, ent);
        cnotGate(4,1, ent);*/
    //    showResult<5>(ent);
}


int main(int argc, char** argv){
    if(argc > 1){
        if(std::string(argv[1]) == "--version"){
            printInfo(MiniQbt::NAME, " : ", MiniQbt::VERSION, "\n");
            return EXIT_SUCCESS;
        }
    }
    printInfo("Welcome by ", MiniQbt::NAME, "\n");


    try{
        
        
        //execute it a hundred times to check the average result
        multiSystemTest();
//        singleSystemTest();

    } catch(const MiniQbt::QuantumException& ex){
        printError("Error program crashed with error : ",ex, "\n");
        return EXIT_FAILURE;
    }
    
    
}