#include "TokenReaders.hpp"
#include <iostream>
#include <regex>
#include "Utils.hpp"
#include <fstream>

std::shared_ptr<Token> TokenReader::parseLine(const std::string& line){
    if(line.length() == 0){
        return nullptr;
    }
    if(line[0] == '/' && line[1] == '/'){
        return nullptr;
    }
    
    std::regex regex_creg_qreg_x_h("\\b(qreg|creg|x|h|)\\s*([a-z|A-Z]+)\\s?\\[([0-9]*)\\](\\s?|\\s*);",std::regex::ECMAScript);//"^[\\s]*Mem\\(([0-9]+)\\)\\s*=\\s*([0-9]+(\\.[0-9]+)?)\\s*$"
    std::smatch m;
    std::regex_match(line, m, regex_creg_qreg_x_h);
    if(m[1] == "qreg"){
        return std::shared_ptr<Token>(new QuantumRegister(m[2], std::stoi(m[3])));
    }
    else if(m[1] == "x"){
        return std::shared_ptr<Token>(new PauliX(m[2],std::stoi(m[3])));
    }
    else if(m[1] == "h"){
        return std::shared_ptr<Token>(new HadamardGate(m[2],std::stoi(m[3])));
    }

    //Checking for measure
    std::regex regex_measure("\\b(measure)\\s*([a-z|A-Z]+)\\s?\\[([0-9])+\\]\\s+->\\s+([a-z|A-Z]+)\\s?\\[([0-9])+\\];",std::regex::ECMAScript);
    std::regex_match(line, m, regex_measure);
    if(m[1] == "measure"){
        return std::shared_ptr<Token>(new Measure(m[2], std::stoi(m[3]), m[4], std::stoi(m[5])));
    }

    //checking for cnot
    std::regex regex_CNot("\\b(cx)\\s*([a-z|A-Z]+)\\s?\\[([0-9])+\\]\\s*\\,\\s*([a-z|A-Z]+)\\s?\\[([0-9])+\\];",std::regex::ECMAScript);
    std::regex_match(line, m, regex_CNot);
    if(m[1] == "cx"){
        return std::shared_ptr<Token>(new CNot(m[2], std::stoi(m[3]), m[4], std::stoi(m[5])));
    }
  
    printWarning("Invalid syntax : ",  line , "\n");
    return nullptr;  
}

FileReader::FileReader(std::function<void ( std::shared_ptr<Token> token)> reader, const std::string& file) : TokenReader::TokenReader(reader) {
    this->file = file;
}

void FileReader::start(){
    std::fstream str(this->file, std::ios::in);
    if(str.good()){
        while(!str.eof()){
           
            std::string line;
            std::getline(str,line);
            std::shared_ptr<Token> res = this->parseLine(line);
            if(res != nullptr){
                reader(res);
            }
        }
    } else {
        printWarning("Could not load file : ",  this->file , "\n");
    }
    str.close();

}

TerminalReader::TerminalReader(std::function<void (std::shared_ptr<Token> token)> reader)  : TokenReader::TokenReader(reader){
    

}



void TerminalReader::start(){
     while(true){
        std::string command;
        std::cout << "$ ";
        std::getline (std::cin,command);
        if(command == "exit"){
            break;
        }
        if(command[0] == '!'){
            std::cout.flush();
            system(command.substr(1).c_str());
            continue;
        }

        std::shared_ptr<Token> res = this->parseLine(command);
        if(res != nullptr){
            reader(res);
        }
    
    }
}