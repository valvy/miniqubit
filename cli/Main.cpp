#include <miniqbt/MiniQbt.hpp>
#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <regex>


std::string filereader(const std::string& fileName){
    std::fstream str(fileName, std::ios::in);
    std::string result = "";
    if(str.good()){
        while(!str.eof()){
            std::string line;
            std::getline(str,line);
            result += line + "\n";
        }
    } else {
        printWarning("Could not load file : ",  fileName, "\n");
    }
    str.close();
    return result;

}

int main(int argc, char** argv){

    MiniQbt::QasmAsyncIntepreter intepreter;
    if(argc > 1){
        if(std::string(argv[1]) == "--version"){
            printInfo(MiniQbt::NAME, " : ", MiniQbt::VERSION, "\n");
            return EXIT_SUCCESS;
        }
        else {
            const std::string src = filereader(std::string(argv[1]));
            intepreter.intepret(src);
            while(intepreter.hasErrors()){
                printError("",intepreter.getError(), "\n");
            }
            
            for(const std::string& reg: intepreter.getRegisters()){
                std::vector<bool> result = intepreter.readClassicRegister(reg);
                std::cout << "Result registery  " << reg << ": ";
                for(const bool& r : result){
                    std::cout << r;
                }
                std::cout << "\n";
            }

            return EXIT_SUCCESS;
        }
    }


   
    printInfo("Welcome by ", MiniQbt::NAME, ",\npress help for help.\n");
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
         
        if(command == "collapse"){
            for(const std::string& reg: intepreter.getRegisters()){
                std::vector<bool> result = intepreter.readClassicRegister(reg);
                std::cout << "Result registery  " << reg << ": ";
                for(const bool& r : result){
                    std::cout << r;
                }
                std::cout << "\n";
            }
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
    
    }
    


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
