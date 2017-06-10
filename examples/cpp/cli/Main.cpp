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

    MiniQbt::QasmAsyncInterpreter interpreter;
    if(argc > 1){
        if(std::string(argv[1]) == "--version"){
            printInfo(MiniQbt::NAME, " : ", MiniQbt::VERSION, "\n");
            return EXIT_SUCCESS;
        }
        else {
            const std::string src = filereader(std::string(argv[1]));
            interpreter.intepret(src);
            while(interpreter.hasErrors()){
                printError("",interpreter.getError(), "\n");
            }
            
            for(const std::string& reg: interpreter.getRegisters()){
                std::vector<bool> result = interpreter.readClassicRegister(reg);
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
            for(const std::string& reg: interpreter.getRegisters()){
                std::vector<bool> result = interpreter.readClassicRegister(reg);
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

        interpreter.intepret(command);
        
        while(interpreter.hasErrors()){
            printError("",interpreter.getError(), "\n");
        }
    
    }
}
