cmake_minimum_required (VERSION 3.5)
project(miniQbt)

LIST( APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake )
include(externalCatch)


SET(miniqbt_destination "bin")
SET(miniqbt_lib_destination "lib")
SET(miniqbt_include_destination "include")

add_subdirectory(MiniQbt)
add_subdirectory(cli)

