#include "core/TokenVisitor.hpp"
//#include "Utils.hpp"
#include <iostream>

using namespace MiniQbt::Core;

TokenVisitor::TokenVisitor(){

}


bool TokenVisitor::hasErrors() const{
    return !errors.empty();
}

std::string TokenVisitor::getError(){
    std::string res = errors.back();
    errors.pop_back();
    return res;
}

void TokenVisitor::visit(CNot& cnot){
    for(AbstractRegister* reg : registers){
        if(reg->getName() == cnot.getLeftHand()){
            reg->visit(cnot);
            return;
        }
    }
    errors.push_back( "Variable :  "+ cnot.getLeftHand() + " Does not exist..");
}

void TokenVisitor::visit(ErrorToken& token){
    errors.push_back(token.getLine());
}

bool TokenVisitor::registerDoesExist(const std::string& name) const{
    for(const AbstractRegister* reg : registers){
        if(reg->getName() == name){
            return true;
        }
    }
    return false;
}

void TokenVisitor::visit(PauliX& pauliGate){
    for(AbstractRegister* reg : registers){
        if(reg->getName() == pauliGate.getName()){
            reg->visit(pauliGate);
            return;
        }
    }
    errors.push_back( "Variable :  " + pauliGate.getName() + " Does not exist..");
}

void TokenVisitor::visit(HadamardGate& hadamard){
    for(AbstractRegister* reg : registers){
        if(reg->getName() == hadamard.getName()){
            reg->visit(hadamard);
            return;
        }
    }
    errors.push_back( "Variable :  " + hadamard.getName() + " Does not exist..");
}

void TokenVisitor::visit(Measure& measure){
    for(AbstractRegister* reg : registers){
        if(reg->getName() == measure.getQureg()){
            //std::cout << "Result : " << reg->visit(measure) << "\n";
            return;
        }
    }
    errors.push_back( "Variable :  " + measure.getQureg() + " Does not exist..");
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


    AbstractRegister* delegate = nullptr;
    switch(registe.getSize()){
        case 0: errors.push_back( "Can we consider a computer without bits a computer??"); return;
        case 1: delegate = new RegisterComposite<1>(registe.getName()); break;
        case 2: delegate = new RegisterComposite<2>(registe.getName()); break;
        case 3: delegate = new RegisterComposite<3>(registe.getName()); break;
        case 4: delegate = new RegisterComposite<4>(registe.getName()); break;
        case 5: delegate = new RegisterComposite<5>(registe.getName()); break;
        case 6: delegate = new RegisterComposite<6>(registe.getName()); break;
        case 7: delegate = new RegisterComposite<7>(registe.getName()); break;
        case 8: delegate = new RegisterComposite<8>(registe.getName()); break;
        case 9: delegate = new RegisterComposite<9>(registe.getName()); break;
        case 10: delegate = new RegisterComposite<10>(registe.getName()); break;
        case 11: delegate = new RegisterComposite<11>(registe.getName()); break;
        case 12: delegate = new RegisterComposite<12>(registe.getName()); break;
        case 13: delegate = new RegisterComposite<13>(registe.getName()); break;
        case 14: delegate = new RegisterComposite<14>(registe.getName()); break;
        case 15: delegate = new RegisterComposite<15>(registe.getName()); break;
        case 16: delegate = new RegisterComposite<16>(registe.getName()); break;
        case 17: delegate = new RegisterComposite<17>(registe.getName()); break;
        case 18: delegate = new RegisterComposite<18>(registe.getName()); break;
        case 19: delegate = new RegisterComposite<19>(registe.getName()); break;
        case 20: delegate = new RegisterComposite<20>(registe.getName()); break;
        default: errors.push_back(
            "size : " + std::to_string(registe.getSize()) + " is to big...\n" +
            "You don't really expect me to calculate approximately " + std::to_string(std::pow(2, registe.getSize())) + " of possibilities??\n" 
        ); return;
    }
    registers.push_back(delegate);

}