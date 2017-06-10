cmake_minimum_required (VERSION 3.5)
project(tests)
add_library(Catch INTERFACE)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

add_subdirectory(Emulator)
add_subdirectory(InterpreterTests)