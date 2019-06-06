cmake_minimum_required (VERSION 3.5)
project(miniQbt)

LIST( APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake )

OPTION(ENABLE_TESTS "Enable unit tests" OFF)
OPTION(ENABLE_PYTHON "Enable building for python" ON)
OPTION(ENABLE_JAVA "Enable building for java" ON)
include(ExternalProject)

IF(ENABLED_TESTS)
    include(externalCatch)
ENDIF()

set(miniQbt_MAJOR_VERSION 0)
set(miniQbt_MINOR_VERSION 6)
set(miniQbt_PATCH_VERSION 1)
set(miniQbt_version ${miniQbt_MAJOR_VERSION}.${miniQbt_MINOR_VERSION}.${miniQbt_PATCH_VERSION})
set(miniQbt_name MiniQbt)

set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for header files")

enable_testing ()
add_subdirectory(modules)

