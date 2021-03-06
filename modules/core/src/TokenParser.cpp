#include "miniqbt/interpreter/TokenParser.hpp"
#include "miniqbt/interpreter/Tokens.hpp"
#include <regex>
#include <iostream>


std::vector<std::shared_ptr<MiniQbt::Core::GateToken>> parseFunction(const std::string& line){
    std::vector<std::shared_ptr<MiniQbt::Core::GateToken>> result;
    std::regex regex_custom_gate("\\s*gate\\s*[a-z|A-Z|0-9]+\\s*\\(?[^\\)]*\\)?\\s*[^{]*\\{[^}]*\\}", std::regex::ECMAScript);
    std::smatch m;//.*{gate\s*[a-z|A-Z|0-9]+}
    auto expression_begin = std::sregex_iterator(line.begin(), line.end(), regex_custom_gate);
    auto expression_end = std::sregex_iterator();

    for (std::sregex_iterator i = expression_begin; i != expression_end; ++i) {
        std::smatch match = *i;
        result.push_back(std::shared_ptr<MiniQbt::Core::GateToken>(new MiniQbt::Core::GateToken(match.str())));
    }
    return result;
}


std::vector<std::shared_ptr<MiniQbt::Core::Token>> MiniQbt::Core::parseExpressions(const std::string& line){
    using namespace MiniQbt::Core;
    std::vector<std::shared_ptr<MiniQbt::Core::Token>> result;
    if(line == ""){
        return result;
    }
    //Filter out all the comments
    const std::regex comment ("(//[^\\n]*\\n)|(//.*?$)",std::regex::ECMAScript);
    std::string removedComments = std::regex_replace (line,comment,"");

    std::vector<std::shared_ptr<MiniQbt::Core::GateToken>> meth = parseFunction(removedComments);
    result.insert(result.end(), meth.begin(), meth.end());
    const std::regex methods ("(\\s*gate\\s*[a-z|A-Z|0-9]+\\s*\\(?[^\\)]*\\)?\\s*[^{]*\\{[^}]*\\})",std::regex::ECMAScript);
    removedComments = std::regex_replace (removedComments,methods,"");

    if(removedComments.find_first_not_of('\n') != std::string::npos){//check if the line is not only new lines
        std::regex splitExpressions("[^;]*;", std::regex::ECMAScript);
        auto expression_begin = std::sregex_iterator(removedComments.begin(), removedComments.end(), splitExpressions);
        auto expression_end = std::sregex_iterator();

        for (std::sregex_iterator i = expression_begin; i != expression_end; ++i) {
            std::smatch match = *i;                                    
            result.push_back(parseToken(match.str()));
            
        }
        if(result.size() == 0){
            result.push_back(std::shared_ptr<Token>(new ErrorToken(line)));
        }
    }
    return result;
}

std::shared_ptr<MiniQbt::Core::Token> MiniQbt::Core::parseToken(const std::string& line){
    using namespace MiniQbt::Core;    
    //std::regex regex_creg_qreg_x_h("\\s*([a-z|A-Z]*)\\s*([a-z|A-Z]+)\\s?\\[([0-9]*)\\](\\s?|\\s*);",std::regex::ECMAScript);
    std::regex regex_creg_qreg_x_h("\\s*([a-z|A-Z]*)\\s*([a-z|A-Z]+)\\s?\\[?([0-9]*)\\]?\\s*;",std::regex::ECMAScript);
    std::smatch m;
    std::regex_match(line, m, regex_creg_qreg_x_h);

    int targetBit = -1;
    if(m[3] != ""){
        targetBit = std::stoi(m[3]);
    }
    if(m[1] == "qreg" && targetBit != -1){
        return std::shared_ptr<Token>(new QuantumRegisterToken(m[2],targetBit));
    } else if(m[1] == "creg" && targetBit != -1){
        return std::shared_ptr<Token>(new ClassicRegisterToken(m[2], targetBit));
    } else if(m[1] == "x"){
        return std::shared_ptr<Token>(new PauliXToken (m[2],targetBit));
    } else if(m[1] == "z"){
        return std::shared_ptr<Token>(new PauliZToken (m[2],targetBit));
    } else if(m[1] == "y"){
        return std::shared_ptr<Token>(new PauliYToken (m[2],targetBit));
    } else if(m[1] == "h"){
        return std::shared_ptr<Token>(new HadamardGateToken(m[2],targetBit));
    } else if(m[1] == "s"){
        return std::shared_ptr<Token>(new PhaseSToken(m[2],targetBit));
    } else if (m[1] == "sdg"){
        return std::shared_ptr<Token>(new PhaseSDGToken(m[2],targetBit));
    } else if (m[1] == "t"){
        return std::shared_ptr<Token>(new PhaseTToken(m[2],targetBit));
    } else if (m[1] == "tdg"){
        return std::shared_ptr<Token>(new PhaseTDGToken(m[2],targetBit));
    }

    std::regex regex_measure("\\s*(measure)\\s*([a-z|A-Z]+)\\s?\\[?([0-9])*\\]?\\s+->\\s+([a-z|A-Z]+)\\s?\\[?([0-9])*\\]?;",std::regex::ECMAScript);
    std::regex_match(line, m, regex_measure);
    if(m[1] == "measure"){
        if(m[3] == "" && m[5] == ""){
            return std::shared_ptr<Token>(new MeasureToken(m[2], m[4]));
        }
        else {
            return std::shared_ptr<Token>(new MeasureToken(m[2], std::stoi(m[3]), m[4], std::stoi(m[5])));
        }
    }

    //checking for cnot
    std::regex regex_CNot("\\s*(cx)\\s*([a-z|A-Z]+)\\s*\\[([0-9])+\\]\\s*\\,\\s*([a-z|A-Z]+)\\s?\\[([0-9])+\\];",std::regex::ECMAScript);
    std::regex_match(line, m, regex_CNot);
    if(m[1] == "cx"){
        return std::shared_ptr<Token>(new CNotToken(m[2], std::stoi(m[3]), m[4], std::stoi(m[5])));
    }

    //Check for the more uncommon tokens
    std::regex regex_assembly_type("\\s*(OPENQASM)\\s+([0-9]*\\.[0-9]*)\\s*;",std::regex::ECMAScript);
    std::regex_match(line, m, regex_assembly_type);
    if(m[1] == "OPENQASM"){
        return std::shared_ptr<Token>(new AssemblyVersionToken(m[2]));
    }

    //include
    std::regex regex_include("\\s*(include)\\s*\\\"([a-z|A-Z|0-9|\\.]*)\\\"\\s*;",std::regex::ECMAScript);
    std::regex_match(line, m, regex_include);
    if(m[1] == "include"){
        return std::shared_ptr<Token>(new IncludeToken(m[2]));
    }

    std::regex regex_barrier("\\s*(barrier)[^;]*;",std::regex::ECMAScript);
    std::regex_match(line, m, regex_barrier);
    if(m[1] == "barrier"){
        return std::shared_ptr<Token>(new BarrierToken());
    }
    return std::shared_ptr<Token>(new ErrorToken("Invalid token: " + line));  
}
