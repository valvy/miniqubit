cmake_minimum_required (VERSION 3.5)
set (CMAKE_CXX_STANDARD 14)
project(JavaNativeMiniQbt)
find_package(JNI REQUIRED)
find_package (Eigen3 3.3 NO_MODULE)

# Make sure we got the provided includes from miniqbt source
GET_DIRECTORY_PROPERTY(
    MINIQBT_INCLUDE_DIRS 
    DIRECTORY ${CMAKE_SOURCE_DIR}/modules/core 
    DEFINITION MINIQBT_INCLUDE_DIRS  
)

SET(NATIVE_LIB_SOURCES 
    ./src/MiniQbtGlobals.cpp
    ./src/MiniQbtQasmAsyncInterpreter.cpp
)

SET(JAVA_NATIVE_LIB_NAME
    JavaMiniQbtWrapper_${CMAKE_SYSTEM_PROCESSOR}_${CMAKE_SYSTEM_NAME}
)

SET(NATIVE_HEADERS
    ${JavaNativeMiniQbt_SOURCE_DIR}/include

)

include_directories(
    ${JNI_INCLUDE_DIRS} 
    ${MINIQBT_INCLUDE_DIRS}
    ${NATIVE_HEADERS}
)
add_library(${JAVA_NATIVE_LIB_NAME} SHARED ${NATIVE_LIB_SOURCES})

target_link_libraries(${JAVA_NATIVE_LIB_NAME} ${JNI_LIBRARIES} Eigen3::Eigen )
