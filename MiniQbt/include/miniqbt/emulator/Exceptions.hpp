#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <string>

namespace MiniQbt{
    class QuantumException{
        private:
        std::string msg;
        public: 
        QuantumException(char const* msg){
            this->msg = std::string(msg);
        }

        QuantumException(const std::string& msg){
            this->msg = std::string(msg);
        }
        std::string getMessage() const{
            return this->msg;
        }
        friend std::ostream& operator<<(std::ostream& os, const QuantumException& state){
            os << state.msg;;
            return os;
        }
    };

    class InvalidInputException : public QuantumException{
        public:
        InvalidInputException(char const * msg) : QuantumException(msg){};
        InvalidInputException(const std::string& msg) : QuantumException(msg){};
    };

    inline void assertInput(const bool as, std::string msg){
        if(as){
            throw InvalidInputException(msg);
        }
    }

}

#endif