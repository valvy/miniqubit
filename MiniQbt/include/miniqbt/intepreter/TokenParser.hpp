#ifndef MINI_QBT_QASM_INTEPRETER_TOKEN_PARSER_HPP
#define MINI_QBT_QASM_INTEPRETER_TOKEN_PARSER_HPP


#include <string>
#include <memory>
#include <vector>

namespace MiniQbt{
    namespace Core{
        class Token;
        /**
        *   Parses a single token.
        **/
        std::shared_ptr<Token> parseToken(const std::string& line);

        /**
        *   Parses an entire string for a list of tokens.
        */
        std::vector<std::shared_ptr<Token>> parseExpressions(const std::string& line);

    }
}

#endif