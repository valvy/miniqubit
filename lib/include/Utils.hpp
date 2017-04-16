#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <iostream>
#include "QuantumState.hpp"

void printProbabilities(const QuantumState& state);

void assertInput(const bool as, std::string msg = "Invalid input detected");

void assertInfinity(const bool as, std::string msg = "Infinity is a long time.." );

template<typename T>
constexpr void printInfo(T& msg){
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        std::cout << msg;
    #else
        std::cout << "\033[1;32m" << msg << "\033[0m";
    #endif
}



template<typename T, typename... arguments>
constexpr void printInfo(T& msg, arguments... args){
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        std::cout<< msg;
    #else
         std::cout << "\033[1;32m" << msg;
    #endif
    printInfo(args...);
}

template<typename T>
constexpr void printError(T& msg){
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        std::cout << msg;
    #else
        std::cout << msg << "\033[0m";
    #endif
}



template<typename T, typename... arguments>
constexpr void printError(T& msg, arguments... args){
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        std::cout<< msg;
    #else
         std::cout << "\033[1;31m" << msg;
    #endif
    printError(args...);
}

#endif