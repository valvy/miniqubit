cmake_minimum_required (VERSION 3.5)
project(emulatorTests)
set (CMAKE_CXX_STANDARD 14)

SET(srcfiles 
    Main.cpp
    HadamardTest.cpp
    quantum_algorithms/GroverTests.cpp
    quantum_algorithms/ShorTests.cpp
    the_weird_and_wonderfull_world_of_the_qubit/SingleQubitTests.cpp
    quantum_algorithms/BasicCircuits.cpp
    quantum_algorithms/learningParity.cpp
    multiple_qubits_gates_and_entangled_states/BellTests.cpp
    multiple_qubits_gates_and_entangled_states/GHZStates.cpp
)

include_directories(
    ../../include 
)

#add_subdirectory(${EXT_PROJECTS_DIR}/catch)
include_directories(${CATCH_INCLUDE_DIR} ${COMMON_INCLUDES})
add_executable(emulatorTests ${srcfiles})
target_link_libraries(emulatorTests Eigen3::Eigen MiniQbt)

add_test(NAME testEmulator COMMAND ${CMAKE_CURRENT_BINARY_DIR}/emulatorTests)