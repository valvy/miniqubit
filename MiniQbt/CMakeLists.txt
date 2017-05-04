cmake_minimum_required (VERSION 3.5)
set (CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib") 
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

set(VERSION_MAJOR "0")
set(VERSION_MINOR "2")
set(VERSION_PATCH "0")
set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

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

include_directories(${MINIQBT_INCLUDE_DIRS} )

add_library(MiniQbt STATIC ${LIB_SOURCES})
target_link_libraries(MiniQbt Eigen3::Eigen)
