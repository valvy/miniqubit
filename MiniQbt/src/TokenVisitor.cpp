#include "miniqbt/intepreter/TokenVisitor.hpp"


using namespace MiniQbt::Core;

TokenVisitor::TokenVisitor(){

}

bool TokenVisitor::doesRegisterExists(const std::string& registerName) const{
    for(const ClassicRegister& reg : classicRegisters){
        if(reg.getName() == registerName){
            return true;
        }
    }
    return false;
}


bool TokenVisitor::hasErrors() const{
    return !errors.empty();
}

std::string TokenVisitor::getError(){
    std::string res = errors.back();
    errors.pop_back();
    return res;
}

std::vector<std::string> TokenVisitor::getClassicRegisters() const{
    std::vector<std::string> result;
    for(const ClassicRegister& bit : classicRegisters){
        result.push_back(bit.getName());
    }
    return result;
}



void TokenVisitor::visit(GateToken& gate){
    customGates.push_back(gate);
}

std::vector<bool> TokenVisitor::getClassicRegister(const std::string& name){
    std::vector<bool> result;
    for(const ClassicRegister& classicReg : classicRegisters){
        if(classicReg.getName() == name){
            for(size_t i = 0; i < classicReg.getSize(); i++ ){
                const Bit bit = classicReg[classicReg.getSize() - i - 1];
               // const Bit bit = classicReg[ i ];
                if(bit.link == ""){
                    result.push_back(0);
                    continue;
                }
                for(AbstractRegister* quantumReg : quantumRegisters){
                    if(bit.link == quantumReg->getName()){
                        quantumReg->collapse();
                        bool res = (*quantumReg)[classicReg.getSize() - bit.quantumPos - 1];
                        //bool res = (*quantumReg)[bit.quantumPos];
                        result.push_back(res);
                    }
                }
            }
        } 
    }
    
    return result;
}

void TokenVisitor::visit(ClassicRegisterToken& regist){
    for(ClassicRegister& reg : classicRegisters){
        if(reg.getName() == reg.getName()){
            reg.setSize(regist.getSize());
            return;
        }
    }

    classicRegisters.push_back(ClassicRegister(regist.getName(), regist.getSize()));
    
}

void TokenVisitor::visit(CNotToken& cnot){
    for(AbstractRegister* reg : quantumRegisters){
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
    for(const AbstractRegister* reg : quantumRegisters){
        if(reg->getName() == name){
            return true;
        }
    }
    return false;
}

void TokenVisitor::visit(PauliXToken& pauliGate){
    for(AbstractRegister* reg : quantumRegisters){
        if(reg->getName() == pauliGate.getName()){
            reg->visit(pauliGate);
            return;
        }
    }
    errors.push_back( "Variable :  " + pauliGate.getName() + " Does not exist..");
}

void TokenVisitor::visit(PauliYToken& pauliGate){
    for(AbstractRegister* reg : quantumRegisters){
        if(reg->getName() == pauliGate.getName()){
            reg->visit(pauliGate);
            return;
        }
    }
    errors.push_back( "Variable :  " + pauliGate.getName() + " Does not exist..");
}

void TokenVisitor::visit(PauliZToken& pauliGate){
    for(AbstractRegister* reg : quantumRegisters){
        if(reg->getName() == pauliGate.getName()){
            reg->visit(pauliGate);
            return;
        }
    }
    errors.push_back( "Variable :  " + pauliGate.getName() + " Does not exist..");
}

void TokenVisitor::visit(HadamardGateToken& hadamard){
    for(AbstractRegister* reg : quantumRegisters){
        if(reg->getName() == hadamard.getName()){
            reg->visit(hadamard);
            return;
        }
    }
    errors.push_back( "Variable :  " + hadamard.getName() + " Does not exist..");
}

void TokenVisitor::visit(MeasureToken& measure){
    for(const AbstractRegister* qReg : quantumRegisters){
        if(qReg->getName() == measure.getQureg()){//quantum register exists
            for(ClassicRegister& cReg : classicRegisters){
                if(cReg.getName() == measure.getClassicReg()){
                    if(measure.linkEntireToken()){
                        if(cReg.getSize() != qReg->getSize()){
                             errors.push_back("Registers are not the same size");
                             return;
                        }


                        std::string errorMsg = "";
                        for(size_t i = 0; i < cReg.getSize(); i++){
                            if(!cReg.linkRegister(i,i, qReg->getName(), errorMsg)){
                                errors.push_back(errorMsg);
                            }
                        }
                    } else {
                        std::string errorMsg = "";
                        if(!cReg.linkRegister(measure.getClassicPos(),measure.getQubitPos(), qReg->getName(), errorMsg)){
                            errors.push_back( errorMsg);
                        }
                    }
                }
            }
            return;
        }
    }
    errors.push_back( "Variable :  " + measure.getQureg() + " Does not exist..");
}

void TokenVisitor::visit(QuantumRegisterToken& registe){
    if(registerDoesExist(registe.getName())){
        size_t remove = 0;
        for(size_t i = 0; i < quantumRegisters.size(); i++){
            if(quantumRegisters[i]->getName() == registe.getName()){
                delete quantumRegisters[i];
                remove = i;
            }
        }
        quantumRegisters.erase(quantumRegisters.begin() + remove);
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
    quantumRegisters.push_back(delegate);

}

 TokenVisitor::~TokenVisitor(){
     for(AbstractRegister* delegate : quantumRegisters){
         delete delegate;
     }
 }