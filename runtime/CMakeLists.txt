cmake_minimum_required (VERSION 3.5)
project(runtimeMiniQbt)
set (CMAKE_CXX_STANDARD 14)
set(CMAKE_C_FLAGS_RELEASE "-O3")


SET(srcfiles 
    Main.cpp
    )

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

include_directories(
    ../MiniQbt/include
)

#include_directories( ${miniQbt_INCLUDE_DIRS} )

add_executable(miniQbt ${srcfiles})
target_link_libraries(miniQbt  Eigen3::Eigen MiniQbt)


install(TARGETS miniQbt DESTINATION "${miniqbt_destination}")


add_custom_target(run
    COMMAND miniQbt
    DEPENDS miniQbt
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
