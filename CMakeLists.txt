cmake_minimum_required (VERSION 3.5)
project(miniQbt)

add_subdirectory(runtime)
add_subdirectory(tests)

enable_testing()
add_test(NAME testMiniQbt COMMAND testMiniQbt)
