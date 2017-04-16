cmake_minimum_required (VERSION 3.7)
project(runtimeMiniQbt)
set (CMAKE_CXX_STANDARD 14)



SET(srcfiles 
    Main.cpp)

include_directories(../lib/include)
add_executable(miniQbt ${srcfiles})
target_link_libraries(miniQbt miniQbtruntime)

add_custom_target(run
    COMMAND miniQbt
    DEPENDS miniQbt
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)