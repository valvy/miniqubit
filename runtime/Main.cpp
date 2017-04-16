#include <QuantumState.hpp>
#include <Gates.hpp>
#include <Utils.hpp>
#include <Globals.hpp>
#include <regex>
#include <utility>

template<size_t size>
void showResult(const QuantumState& reg){
    std::vector<std::pair<std::bitset<size>, size_t>> outcomes;
    std::random_device rd;
    std::default_random_engine generator(rd());
    for(size_t i = 0; i < 10000; i++){
        std::bitset<size> outcom =  measure<size>(reg, generator);
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
    QuantumState q0 = QuantumState::getZero();
    QuantumState q1 = QuantumState::getZero();
    QuantumState q2 = QuantumState::getZero();
    QuantumState ent(q0,q1);
    ent = QuantumState(ent,q2); //entangle them first :)
    hadamardGate(1, ent);
    hadamardGate(2, ent);
    hadamardGate(2, ent);
    cnotGate(1,2, ent);
    hadamardGate(2,ent);
    hadamardGate(1, ent);
    hadamardGate(2, ent);
    pauliX(1,ent);
    pauliX(2,ent);
    hadamardGate(2, ent);
    cnotGate(1,2, ent);
    hadamardGate(2,ent);
    pauliX(1, ent);
    pauliX(2, ent);
    hadamardGate(1, ent);
    hadamardGate(2, ent);
    showResult<3>(ent);
}


int main(int argc, char** argv){
    if(argc > 1){
        if(std::string(argv[1]) == "--version"){
            printInfo(Globals::NAME, " : ", Globals::VERSION, "\n");
            return EXIT_SUCCESS;
        }
    }
    printInfo("Welcome by ", Globals::NAME, "\n");


    try{
        
        
        //execute it a hundred times to check the average result
        multiSystemTest();
//        singleSystemTest();

    } catch(const QuantumException& ex){
        printError("Error program crashed with error : ",ex, "\n");
        return EXIT_FAILURE;
    }
    
    
}