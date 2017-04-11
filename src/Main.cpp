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
    std::random_device rd;
    std::default_random_engine generator(rd());
    QuantumState q1 = QuantumState::getZero();
    QuantumState q2 = QuantumState::getZero();
    QuantumState z = QuantumState::getZero();
    try{
        hadamardGate(0,q1);
        hadamardGate(0,q2);
        QuantumState ent(q1, q2);
        cnotGate(0,1, ent);
        ent = QuantumState(ent, z);
        cnotGate(1,2, ent);

        constexpr size_t size = 3;

        std::vector<std::pair<std::bitset<size>, size_t>> outcomes;

        for(size_t i = 0; i < 100; i++){
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

        for(const auto& result : outcomes){
            std::cout << "result : " << result.first << " | " << result.second << "\n";
        }
       
   

    } catch(const QuantumException& ex){
        printError("Error program crashed with error : ",ex, "\n");
        return EXIT_FAILURE;
    }
    
    
}