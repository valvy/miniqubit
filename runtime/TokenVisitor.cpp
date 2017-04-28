#include "TokenVisitor.hpp"
#include "Utils.hpp"
#include <iostream>

TokenVisitor::TokenVisitor(){

}

void TokenVisitor::visit(CNot& cnot){
    for(AbstractDelegate* reg : registers){
        if(reg->getName() == cnot.getLeftHand()){
            reg->visit(cnot);
            return;
        }
    }
    printError( "Variable :  ", cnot.getLeftHand() , " Does not exist..");
}

bool TokenVisitor::registerDoesExist(const std::string& name) const{
    for(const AbstractDelegate* reg : registers){
        if(reg->getName() == name){
            return true;
        }
    }
    return false;
}

void TokenVisitor::visit(PauliX& pauliGate){
    for(AbstractDelegate* reg : registers){
        if(reg->getName() == pauliGate.getName()){
            reg->visit(pauliGate);
            return;
        }
    }
    printError( "Variable :  ", pauliGate.getName() , " Does not exist..");
}

void TokenVisitor::visit(HadamardGate& hadamard){
    for(AbstractDelegate* reg : registers){
        if(reg->getName() == hadamard.getName()){
            reg->visit(hadamard);
            return;
        }
    }
    printError( "Variable :  ", hadamard.getName() , " Does not exist..");
}

void TokenVisitor::visit(Measure& measure){
    for(AbstractDelegate* reg : registers){
        if(reg->getName() == measure.getQureg()){
            std::cout << "Result : " << reg->visit(measure) << "\n";
            return;
        }
    }
    printError( "Variable :  ", measure.getQureg() , " Does not exist..");
}

void TokenVisitor::visit(QuantumRegister& registe){
    if(registerDoesExist(registe.getName())){
        size_t remove = 0;
        for(size_t i = 0; i < registers.size(); i++){
            if(registers[i]->getName() == registe.getName()){
                delete registers[i];
                remove = i;
            }
        }
        registers.erase(registers.begin() + remove);
    }


    AbstractDelegate* delegate = nullptr;
    switch(registe.getSize()){
        case 0: printError( "Can we consider a computer without bits a computer??"); return;
        case 1: delegate = new RegisterDelegate<1>(registe.getName()); break;
        case 2: delegate = new RegisterDelegate<2>(registe.getName()); break;
        case 3: delegate = new RegisterDelegate<3>(registe.getName()); break;
        case 4: delegate = new RegisterDelegate<4>(registe.getName()); break;
        case 5: delegate = new RegisterDelegate<5>(registe.getName()); break;
        case 6: delegate = new RegisterDelegate<6>(registe.getName()); break;
        case 7: delegate = new RegisterDelegate<7>(registe.getName()); break;
        case 8: delegate = new RegisterDelegate<8>(registe.getName()); break;
        case 9: delegate = new RegisterDelegate<9>(registe.getName()); break;
        case 10: delegate = new RegisterDelegate<10>(registe.getName()); break;
        case 11: delegate = new RegisterDelegate<11>(registe.getName()); break;
        case 12: delegate = new RegisterDelegate<12>(registe.getName()); break;
        case 13: delegate = new RegisterDelegate<13>(registe.getName()); break;
        case 14: delegate = new RegisterDelegate<14>(registe.getName()); break;
        case 15: delegate = new RegisterDelegate<15>(registe.getName()); break;
        case 16: delegate = new RegisterDelegate<16>(registe.getName()); break;
        case 17: delegate = new RegisterDelegate<17>(registe.getName()); break;
        case 18: delegate = new RegisterDelegate<18>(registe.getName()); break;
        case 19: delegate = new RegisterDelegate<19>(registe.getName()); break;
        case 20: delegate = new RegisterDelegate<20>(registe.getName()); break;
        default: printError(
            "size : ", registe.getSize(), " is to big...\n",
            "You don't really expect me to calculate approximately ", std::pow(2, registe.getSize()), " of possibilities??\n" 
        ); return;
    }
    registers.push_back(delegate);

}