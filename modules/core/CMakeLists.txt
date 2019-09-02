cmake_minimum_required (VERSION 3.5)
set (CMAKE_CXX_STANDARD 14)

PROJECT(MiniQbt VERSION ${miniQbt_version})

IF(ENABLE_EMSCRIPTEN)
SET( CMAKE_CXX_COMPILER "em++")
ENDIF()
find_package (Eigen3 3.3 REQUIRED NO_MODULE)



SET(LIB_SOURCES 
    src/QuantumResult.cpp
    src/QasmAsyncInterpreter.cpp
    src/Tokens.cpp
    src/TokenVisitor.cpp
    src/Emscripten.cpp
    src/TokenParser.cpp
    src/ClassicRegister.cpp
    src/exceptions/InterpreterExceptions.cpp
  
)
set(header_version_in ${MiniQbt_SOURCE_DIR}/cmake/MiniQbt.hpp.in)
set(header_version_out ${CMAKE_CURRENT_BINARY_DIR}/include/miniqbt/MiniQbt.hpp)
configure_file(${header_version_in} ${header_version_out})

set(MINIQBT_INCLUDE_DIRS ${MiniQbt_SOURCE_DIR}/include/ ${CMAKE_CURRENT_BINARY_DIR}/include/ ) 
include_directories(${MINIQBT_INCLUDE_DIRS} )

if(ENABLE_EMSCRIPTEN)
  add_executable("${PROJECT_NAME}.js" ${LIB_SOURCES} ${MINIQBT_INCLUDE_DIRS} )
  ADD_DEFINITIONS( "-g -Wall -c --bind" )
  SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} --bind")
  target_link_libraries("${PROJECT_NAME}.js" Eigen3::Eigen)
ELSE()
  if(NOT WIN32)
  ADD_DEFINITIONS( "-g -Wall -fPIC -Werror" )
  
  endif()

  add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES})
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
  IF(ENABLE_TESTS)
  add_subdirectory(tests)
  ENDIF()


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
ENDIF()