#ifndef MINI_QBT_QASM_INTEPRETER_CORE_CLASSIC_REGISTER_HPP
#define MINI_QBT_QASM_INTEPRETER_CORE_CLASSIC_REGISTER_HPP


#include <string>
#include <vector>


namespace MiniQbt{
    namespace Core{

        class AbstractRegister;
        /**
        *   Storage of a possible future bit.
        *   Contains data of the future result, such as the future bit set and where to read it from.
        *   @author Heiko van der Heijden
        **/
        struct Bit{
                int bitPos;
                int quantumPos;
                std::string link;
                Bit(int bitPos, int quantumPos, std::string link) :
                bitPos(bitPos), quantumPos(quantumPos), link(link) { }      
         };

         /**
         *  This class allows you to dynamicly allocate quantum bits to a classical register.
         *  It stores the bit order, where it receives it's bit.
         *  @author Heiko van der Heijden
         */
        class ClassicRegister{
            private:
            std::string name;
            std::vector<Bit> data;
            int size;
            public:
            ClassicRegister(std::string name, int size) : name(name), size(size){}
            Bit operator[] (int position) const;
            std::string getName() const;
            void setSize(const int& size);
            int getSize() const { return size; }
            bool linkRegister(int bitPos, int quantumPos, const std::string& link, std::string& errorMsg);
        };
    }
}

#endif