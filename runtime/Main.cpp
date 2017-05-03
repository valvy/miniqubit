#include <MiniQbtEmulator.hpp>
#include <QasmAsyncIntepreter.hpp>
#include "Utils.hpp"
#include <iostream>

int main(int argc, char** argv){

    MiniQbt::QasmAsyncIntepreter intepreter;
    intepreter.intepret("qreg q[5];");
    intepreter.intepret("creg c[5];");
    intepreter.intepret("h q[2];");
    intepreter.intepret("measure q[0] -> c[0];");
    intepreter.intepret("measure q[1] -> c[1];");
    intepreter.intepret("measure q[2] -> c[2];");
    intepreter.intepret("measure q[3] -> c[3];");
    intepreter.intepret("measure q[4] -> c[4];");
    auto res = intepreter.readClassicRegister("c");
    while(intepreter.hasErrors()){
        printError("",intepreter.getError(), "\n");
    }
    std::cout << "result : ";
    for(bool d : res){
        std::cout << d;
    }
    std::cout << "\n";

   /* printInfo("Welcome by ", MiniQbt::NAME, ",\npress help for help.\n");
    while(true){
        
        std::string command;
        std::cout << "$ ";
        std::getline (std::cin,command);

        if(command == "exit"){
            printInfo("Bye \n");
            break;
        }
        if(command == "about"){
            printInfo(MiniQbt::NAME, " : ", MiniQbt::VERSION, "\n");
            printInfo("Build date: " , __DATE__," ", __TIME__, "\n");
            std::cout << "Created by Heiko van der Heijden\n";
            continue;
        }
        if(command == "help"){
            printInfo(
                "Interactive shell for the Qasm language\n",
                "Exit program -> exit \n",
                "Show version -> about \n"
            );
            continue;
        }

        if(command[0] == '!'){
            std::cout.flush();
            system(command.substr(1).c_str());
            continue;
        }

        intepreter.intepret(command);
        
        while(intepreter.hasErrors()){
            printError("",intepreter.getError(), "\n");
        }
    
    }*/
    


/*
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
    reader->start();*/
    
    
}
