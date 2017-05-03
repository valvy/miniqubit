#include "core/TokenParser.hpp"
#include <regex>
#include "core/Tokens.hpp"

std::shared_ptr<MiniQbt::Core::Token> MiniQbt::Core::parseToken(const std::string& line){
    using namespace MiniQbt::Core;
    if(line[0] == '/' && line[1] == '/'){
        return std::shared_ptr<Token>(new CommentToken());
    }

    std::regex regex_creg_qreg_x_h("\\b(qreg|creg|x|h|)\\s*([a-z|A-Z]+)\\s?\\[([0-9]*)\\](\\s?|\\s*);",std::regex::ECMAScript);
    std::smatch m;
    std::regex_match(line, m, regex_creg_qreg_x_h);
    if(m[1] == "qreg"){
        return std::shared_ptr<Token>(new QuantumRegisterToken(m[2], std::stoi(m[3])));
    }
    else if(m[1] == "creg"){
        return std::shared_ptr<Token>(new ClassicRegisterToken(m[2], std::stoi(m[3])));
    }
    else if(m[1] == "x"){
        return std::shared_ptr<Token>(new PauliXToken (m[2],std::stoi(m[3])));
    }
    else if(m[1] == "h"){
        return std::shared_ptr<Token>(new HadamardGateToken(m[2],std::stoi(m[3])));
    }

    //Checking for measure
    std::regex regex_measure("\\b(measure)\\s*([a-z|A-Z]+)\\s?\\[([0-9])+\\]\\s+->\\s+([a-z|A-Z]+)\\s?\\[([0-9])+\\];",std::regex::ECMAScript);
    std::regex_match(line, m, regex_measure);
    if(m[1] == "measure"){
        return std::shared_ptr<Token>(new MeasureToken(m[2], std::stoi(m[3]), m[4], std::stoi(m[5])));
    }

    //checking for cnot
    std::regex regex_CNot("\\b(cx)\\s*([a-z|A-Z]+)\\s?\\[([0-9])+\\]\\s*\\,\\s*([a-z|A-Z]+)\\s?\\[([0-9])+\\];",std::regex::ECMAScript);
    std::regex_match(line, m, regex_CNot);
    if(m[1] == "cx"){
        return std::shared_ptr<Token>(new CNotToken(m[2], std::stoi(m[3]), m[4], std::stoi(m[5])));
    }
  
 //   printWarning("Invalid syntax : ",  line , "\n");
    return std::shared_ptr<Token>(new ErrorToken("Invalid token on " + line));  
}