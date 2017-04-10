#include "QuantumState.hpp"
#include "Gates.hpp"
#include "Utils.hpp"
#include "Globals.hpp"
#include <regex>


int main(int argc, char** argv){
    if(argc > 1){
        if(std::string(argv[1]) == "--version"){
            printInfo(Globals::NAME, " : ", Globals::VERSION, "\n");
            return EXIT_SUCCESS;
        }
    }
    printInfo("Welcome by ", Globals::NAME, "\n");
  
    QuantumState q1 = QuantumState::getZero();
    QuantumState q2 = QuantumState::getZero();
    try{
        hadamardGate(0,q1);
        QuantumState ent(q1, q2);
        cnotGate(0,1, ent);
        ent = QuantumState(q2,ent);
        cnotGate(1,2, ent);
        std::cout << measure<3>(ent) << "\n";

      /*  ent = QuantumState(q1, ent);
        hadamardGate(0, ent);
        cnotGate(2,0, ent);
        std::cout << measure<3>(ent) << "\n";*/
   

    } catch(const QuantumException& ex){
        printError("Error program crashed with error : ",ex, "\n");
        return EXIT_FAILURE;
    }
    
    
}