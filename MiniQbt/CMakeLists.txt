cmake_minimum_required (VERSION 3.5)
set (CMAKE_CXX_STANDARD 14)
PROJECT(miniQbt)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

SET(LIB_SOURCES 
    src/QasmAsyncIntepreter.cpp
    src/Tokens.cpp
    src/TokenVisitor.cpp
    src/TokenParser.cpp
    src/ClassicRegister.cpp
)

set(MINIQBT_INCLUDE_DIRS
    ${miniQbt_SOURCE_DIR}/include
)

set(PUBLIC_INCLUDES
    ${miniQbt_SOURCE_DIR}/include/miniqbt/MiniQbt.hpp
    ${miniQbt_SOURCE_DIR}/include/miniqbt/emulator/*.hpp
    ${miniQbt_SOURCE_DIR}/include/miniqbt/emulator/tools/*.hpp
    ${miniQbt_SOURCE_DIR}/include/miniqbt/intepreter/*.hpp
)

include_directories(${MINIQBT_INCLUDE_DIRS} )



add_library(MiniQbt SHARED ${LIB_SOURCES})
target_link_libraries(MiniQbt Eigen3::Eigen)

install(TARGETS MiniQbt DESTINATION ${miniqbt_lib_destination} )
install(FILES ${PUBLIC_INCLUDES} DESTINATION ${miniqbt_include_destination})

add_subdirectory(tests)