#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <iostream>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <windows.h>
#endif

template<typename T>
constexpr void printInfo(T& msg){
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 2);
        std::cout << msg;
		SetConsoleTextAttribute(hConsole, 7);
    #else
        std::cout << "\033[1;32m" << msg << "\033[0m";
    #endif
}

template<typename T, typename... arguments>
constexpr void printInfo(T& msg, arguments... args) {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 2);
	std::cout << msg;
	SetConsoleTextAttribute(hConsole, 7);
#else
	std::cout << "\033[1;32m" << msg;
#endif
	printInfo(args...);
}


template<typename T>
constexpr void printWarning(T& msg){
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 14);
	std::cout << msg;
	SetConsoleTextAttribute(hConsole, 7);
    #else
        std::cout << "\033[1;33m" << msg << "\033[0m";
    #endif
}

template<typename T, typename... arguments>
constexpr void printWarning(T& msg, arguments... args){
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 14);
	std::cout << msg;
	SetConsoleTextAttribute(hConsole, 7);
    #else
         std::cout << "\033[1;33m" << msg;
    #endif
    printWarning(args...);
}


template<typename T>
constexpr void printError(T& msg){
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 4);
	std::cout << msg;
	SetConsoleTextAttribute(hConsole, 7);
    #else
        std::cout << msg << "\033[0m";
    #endif
}



template<typename T, typename... arguments>
constexpr void printError(T& msg, arguments... args){
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 4);
	std::cout << msg;
	SetConsoleTextAttribute(hConsole, 7);
    #else
         std::cout << "\033[1;31m" << msg;
    #endif
    printError(args...);
}

#endif