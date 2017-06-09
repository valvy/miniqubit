cmake_minimum_required (VERSION 3.5)
set (CMAKE_CXX_STANDARD 14)

PROJECT(MiniQbt VERSION ${miniQbt_version})


find_package (Eigen3 3.3 REQUIRED NO_MODULE)



SET(LIB_SOURCES 
    src/QasmAsyncIntepreter.cpp
    src/Tokens.cpp
    src/TokenVisitor.cpp
    src/TokenParser.cpp
    src/ClassicRegister.cpp
)
set(header_version_in ${MiniQbt_SOURCE_DIR}/cmake/MiniQbt.hpp.in)
set(header_version_out ${CMAKE_CURRENT_BINARY_DIR}/include/miniqbt/MiniQbt.hpp)
configure_file(${header_version_in} ${header_version_out})

set(MINIQBT_INCLUDE_DIRS ${MiniQbt_SOURCE_DIR}/include/ ${CMAKE_CURRENT_BINARY_DIR}/include/ ) 
include_directories(${MINIQBT_INCLUDE_DIRS} )


if(WIN32)
  
	add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES})
else()
  ADD_DEFINITIONS( "-g -Wall -fPIC -Werror" )
	add_library(${PROJECT_NAME} SHARED ${LIB_SOURCES})
endif()

target_link_libraries(${PROJECT_NAME} Eigen3::Eigen)


configure_file(
    ${MiniQbt_SOURCE_DIR}/cmake/Config.cmake.in 
    "${PROJECT_BINARY_DIR}/miniqbtConfig.cmake" @ONLY)

if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR CMake)
else()
  set(DEF_INSTALL_CMAKE_DIR lib/CMake/miniqbt)
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH "Installation directory for CMake files")


foreach(p LIB BIN INCLUDE CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()

#setup tests
add_subdirectory(tests)



export(TARGETS ${PROJECT_NAME}
  FILE "${PROJECT_BINARY_DIR}/miniqbtTargets.cmake")

export(PACKAGE ${PROJECT_NAME})

file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
   "${INSTALL_INCLUDE_DIR}")

set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")

configure_file(cmake/Config.cmake.in
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/miniqbtConfig.cmake" @ONLY)

configure_file(cmake/Version.cmake.in
  "${PROJECT_BINARY_DIR}/miniqbtConfigVersion.cmake" @ONLY)

install(FILES
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/miniqbtConfig.cmake"
  "${PROJECT_BINARY_DIR}/miniqbtConfigVersion.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)

install(TARGETS ${PROJECT_NAME} DESTINATION ${INSTALL_LIB_DIR} )
install( DIRECTORY ${MINIQBT_INCLUDE_DIRS} DESTINATION ${INSTALL_INCLUDE_DIR} FILES_MATCHING PATTERN "*.hpp*" )
