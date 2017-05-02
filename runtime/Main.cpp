#include <MiniQbt.hpp>
#include "Utils.hpp"
#include "TokenReaders.hpp"
#include "TokenVisitor.hpp"
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

template<size_t qubitSize>
void speedTest(size_t amount){
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed_seconds;
    start = std::chrono::system_clock::now();
    std::bitset<qubitSize> bitset;
    for(size_t i = 0; i < amount; i++){
        MiniQbt::QuantumEmulator<qubitSize, true> emulator;
        auto ent = emulator.generateRegister();
        emulator.pauliX(1,ent);
        emulator.hadamardGate(0,ent);
        emulator.hadamardGate(1,ent);
        emulator.controlledNot(0,1,ent);
        emulator.hadamardGate(0,ent);
        emulator.hadamardGate(1,ent);
        bitset = emulator.measure(ent, generator);
        //std::cout << bitset << "\n";
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    std::cout << qubitSize << " Solved in : " << elapsed_seconds.count() << "Last answer was " << bitset << " amount of time passed \n";
}

int main(int argc, char** argv){


    TokenVisitor visitor;
    std::shared_ptr<TokenReader> reader = nullptr;
    auto tokenizer = [&](const std::shared_ptr<Token>& token) -> void {
        try{
            token->accept(visitor);
        } catch(const MiniQbt::QuantumException& ex){
            printError("An error has occured: ",ex, "\n");
        }
    };

    if(argc > 1){
        if(std::string(argv[1]) == "--version"){
            printInfo(MiniQbt::NAME, " : ", MiniQbt::VERSION, "\n");
            return EXIT_SUCCESS;
        }
        reader = std::shared_ptr<TokenReader>(new FileReader(tokenizer, argv[1]));
    } else {
        printInfo("Welcome by ", MiniQbt::NAME, ",\npress help for help.\n");
        reader = std::shared_ptr<TokenReader>(new TerminalReader(tokenizer));
    }
    reader->start();
    
    
}
