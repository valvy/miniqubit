cmake_minimum_required (VERSION 3.5)
project(emulatorTests)
set (CMAKE_CXX_STANDARD 14)



add_library(Catch INTERFACE)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)


SET(srcfiles 
    Main.cpp
    HadamardTest.cpp
    GroverTests.cpp
    ShorTests.cpp
    SingleQubitTests.cpp
    BasicCircuits.cpp
    learningParity.cpp
)


include_directories(${CATCH_INCLUDE_DIR} ${COMMON_INCLUDES})
include_directories(../../lib/MiniQbtEmulator)
add_executable(emulatorTests ${srcfiles})
target_link_libraries(emulatorTests Eigen3::Eigen)

add_custom_target(tests
    COMMAND emulatorTests
    DEPENDS emulatorTests
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
