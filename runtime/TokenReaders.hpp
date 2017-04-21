#ifndef MINI_QBT_TOKEN_READERS_HPP
#define MINI_QBT_TOKEN_READERS_HPP

#include <functional>
#include <vector>
#include <memory>
#include "Tokens.hpp"

class TokenReader{
    protected:
    std::function<void ( std::shared_ptr<Token> token)> reader;
    
    std::shared_ptr<Token> parseLine(const std::string& line);
    public:
    TokenReader(std::function<void (std::shared_ptr<Token> token)> reader) : reader(reader){}
    virtual void start() = 0;
};

class FileReader : public TokenReader{
    std::string file;
    public:
    FileReader(std::function<void ( std::shared_ptr<Token> token)> reader, const std::string& file);
    virtual void start() override;
};

class TerminalReader : public TokenReader{
    public:
    TerminalReader(std::function<void ( std::shared_ptr<Token> token)> reader);
    virtual void start() override;
};


#endif
