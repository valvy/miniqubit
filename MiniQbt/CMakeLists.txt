cmake_minimum_required (VERSION 3.5)
set (CMAKE_CXX_STANDARD 14)
if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

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

install(TARGETS MiniQbt DESTINATION ${miniqbt_lib_destination} )
#install( DIRECTORY ${miniQbt_SOURCE_DIR}/include/ DESTINATION ${miniqbt_include_destination} FILES_MATCHING PATTERN "*.hpp*" )

#setup tests

#add_subdirectory(tests)


