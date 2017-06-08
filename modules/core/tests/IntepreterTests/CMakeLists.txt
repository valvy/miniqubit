cmake_minimum_required (VERSION 3.5)
project(IntepreterTests)
set (CMAKE_CXX_STANDARD 14)

SET(srcfiles 
    Main.cpp
    SimpleAsyncTests.cpp
    ResultChecks.cpp
    SyntaxTests.cpp
)

include_directories(
    ../../include 
)
#add_subdirectory(${EXT_PROJECTS_DIR}/catch)

include_directories(${CATCH_INCLUDE_DIR} ${COMMON_INCLUDES})
add_executable(IntepreterTests ${srcfiles})
target_link_libraries(IntepreterTests Eigen3::Eigen MiniQbt)

add_custom_target(IntepreterTest
    COMMAND IntepreterTests
    DEPENDS IntepreterTests
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
add_test(NAME testIntepreter COMMAND ${CMAKE_CURRENT_BINARY_DIR}/IntepreterTests)