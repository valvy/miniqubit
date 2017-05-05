#ifndef MINI_QBT_QASM_INTEPRETER_CORE_CLASSIC_REGISTER_HPP
#define MINI_QBT_QASM_INTEPRETER_CORE_CLASSIC_REGISTER_HPP

#include <string>
#include <vector>


namespace MiniQbt{
    namespace Core{

        class AbstractRegister;

        struct Bit{
                size_t bitPos;
                size_t quantumPos;
                std::string link;
                Bit(size_t bitPos, size_t quantumPos, std::string link) :
                bitPos(bitPos), quantumPos(quantumPos), link(link) { }
         };

        class ClassicRegister{
            private:
            std::string name;
            std::vector<Bit> data;
            size_t size;
            public:
            ClassicRegister(std::string name, size_t size) : name(name), size(size){}
            Bit operator[] (int position) const;
            std::string getName() const;
            void setSize(const size_t& size);
            size_t getSize() const { return size; }
            bool linkRegister(size_t bitPos, size_t quantumPos, const std::string& link, std::string& errorMsg);
        };
    }
}

#endif