#include "QuantumState.hpp"
#include "Gates.hpp"
#include "Utils.hpp"
#include "Globals.hpp"
#include <regex>
#include <utility>

int main(int argc, char** argv){
    if(argc > 1){
        if(std::string(argv[1]) == "--version"){
            printInfo(Globals::NAME, " : ", Globals::VERSION, "\n");
            return EXIT_SUCCESS;
        }
    }
    printInfo("Welcome by ", Globals::NAME, "\n");


    try{
        constexpr size_t size = 3;
        std::vector<std::pair<std::bitset<size>, size_t>> outcomes;
        //execute it a hundred times to check the average result
        
            std::random_device rd;
            std::default_random_engine generator(rd());
        /*    QuantumState reg(size);
            hadamardGate(0,reg);
            hadamardGate(1,reg);
           
            cnotGate(0,1, reg);
            cnotGate(1,2, reg);
            //std::cout << reg << "\n";
            hadamardGate(1,reg);*/
          //  std::cout << reg << "\n";
            QuantumState q1 = QuantumState::getZero();
            QuantumState q2 = QuantumState::getZero();
            QuantumState z = QuantumState::getZero();
            hadamardGate(0,q2);
            hadamardGate(0,q1);
            QuantumState ent(q1, q2);
            //std::cout << ent.getState() << "\n";
            cnotGate(0,1, ent);
          //  hadamardGate(0,ent);
            ent =  QuantumState(ent,z);
            cnotGate(1,2, ent);
            hadamardGate(1,ent);
            
          //  hadamardGate(1,ent);
        for(size_t i = 0; i < 10000; i++){
            std::bitset<size> outcom =  measure<size>(ent, generator);
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
       
   

    } catch(const QuantumException& ex){
        printError("Error program crashed with error : ",ex, "\n");
        return EXIT_FAILURE;
    }
    
    
}