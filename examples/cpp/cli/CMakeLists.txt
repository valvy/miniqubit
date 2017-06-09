cmake_minimum_required (VERSION 3.5)
project(cliMiniQbt)
set (CMAKE_CXX_STANDARD 14)
set(CMAKE_C_FLAGS_RELEASE "-O3")
find_library(MiniQbt REQUIRED)

SET(srcfiles 
    Main.cpp
    )

find_package (Eigen3 3.3 REQUIRED NO_MODULE)
#find_package(MiniQbt REQUIRED NO_MODULE)

add_executable(miniQbt ${srcfiles})
target_link_libraries(miniQbt  Eigen3::Eigen MiniQbt)

