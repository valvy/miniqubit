cmake_minimum_required (VERSION 3.5)
project(emulatorTests)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_CXX_STANDARD 14)

SET(srcfiles 
    Main.cpp
    HadamardTest.cpp
    GroverTests.cpp
    ShorTests.cpp
    SingleQubitTests.cpp
    BasicCircuits.cpp
    learningParity.cpp
)

include_directories(
    ../../include 
)


include_directories(${CATCH_INCLUDE_DIR} ${COMMON_INCLUDES})
add_executable(emulatorTests ${srcfiles})
target_link_libraries(emulatorTests Eigen3::Eigen)

add_custom_target(emulatorTest
    COMMAND emulatorTests
    DEPENDS emulatorTests
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
add_test(testEmulator emulatorTests)