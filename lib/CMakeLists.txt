cmake_minimum_required (VERSION 3.7)
project(libminiQbtruntime)
set (CMAKE_CXX_STANDARD 14)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

SET(srcfiles 
    src/Gates.cpp 
    src/Exceptions.cpp 
    src/QuantumState.cpp 
    src/Utils.cpp
)


include_directories(include)
add_library(miniQbtruntime ${srcfiles})
target_link_libraries(miniQbtruntime  Eigen3::Eigen)