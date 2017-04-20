cmake_minimum_required (VERSION 3.7)
project(miniqbtTests)
set (CMAKE_CXX_STANDARD 14)

LIST( APPEND CMAKE_MODULE_PATH ${miniqbtTests_SOURCE_DIR}/cmake )
include(externalCatch)

add_library(Catch INTERFACE)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)


SET(srcfiles 
    Main.cpp
    HadamardTest.cpp
    GroverTests.cpp
    ShorTests.cpp
    SingleQubitTests.cpp
)


include_directories(${CATCH_INCLUDE_DIR} ${COMMON_INCLUDES})
include_directories(../lib)
add_executable(testMiniQbt ${srcfiles})
target_link_libraries(testMiniQbt Eigen3::Eigen)

add_custom_target(tests
    COMMAND testMiniQbt
    DEPENDS testMiniQbt
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)