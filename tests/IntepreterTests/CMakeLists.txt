cmake_minimum_required (VERSION 3.5)
project(IntepreterTests)
set (CMAKE_CXX_STANDARD 14)


SET(srcfiles 
    Main.cpp
    SimpleAsyncTests.cpp
)

include_directories(
    ../../lib/MiniQbtEmulator 
    ../../lib/QasmIntepreter/include
)


include_directories(${CATCH_INCLUDE_DIR} ${COMMON_INCLUDES})
add_executable(IntepreterTests ${srcfiles})
target_link_libraries(IntepreterTests Eigen3::Eigen QasmIntepreter)

add_custom_target(IntepreterTest
    COMMAND IntepreterTests
    DEPENDS IntepreterTests
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
