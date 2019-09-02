cmake_minimum_required (VERSION 3.5)
project(miniQbt)


IF(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    # Check if you're in the root directory of the project, and give an error.
    MESSAGE(FATAL_ERROR "Please create a dedicated build directory for MiniQbt. (You may need remove the CmakeCache.txt and the cache)")
ENDIF()


LIST( APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake )

OPTION(ENABLE_EMSCRIPTEN "Enable Emscripten" OFF)

OPTION(ENABLE_TESTS "Enable unit tests" OFF)
OPTION(ENABLE_JAVA "Enable building for java" OFF)
OPTION(ENABLE_PYTHON "Enable building for python" OFF)

SET (
    MINIQBT_PLATFORM_NAME ${CMAKE_SYSTEM_PROCESSOR}_${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_VERSION}
)

IF(ENABLE_EMSCRIPTEN)
    # Check if the emsdk is defined
    IF("$ENV{EMSDK}" STREQUAL "")
        MESSAGE(FATAL_ERROR "Missing the Emscripten SDK. Please set this up.")
    ENDIF()
    # Disable the unit test and wrappers when building for EMSCRIPTEN
    SET (
        MINIQBT_PLATFORM_NAME Emscript
    )
    IF(ENABLE_TESTS OR ENABLE_JAVA OR ENABLE_PYTHON)
        MESSAGE(FATAL_ERROR "You can't build the python/java bindings or perform unit tests while also using emscripten. Please check your settings")
    ENDIF()

ENDIF()


IF(ENABLE_TESTS)
include(ExternalProject)
include(externalCatch)
enable_testing ()
ENDIF()

set(miniQbt_MAJOR_VERSION 1)
set(miniQbt_MINOR_VERSION 0)
set(miniQbt_PATCH_VERSION 0)
set(miniQbt_version ${miniQbt_MAJOR_VERSION}.${miniQbt_MINOR_VERSION}.${miniQbt_PATCH_VERSION})
set(miniQbt_name MiniQbt_${MINIQBT_PLATFORM_NAME})

set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for header files")

add_subdirectory(doc)
add_subdirectory(modules)

