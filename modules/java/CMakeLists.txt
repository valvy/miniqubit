cmake_minimum_required (VERSION 3.5)
project(JavaMiniQbt)
find_package(Java REQUIRED)
find_package(JNI REQUIRED)
find_package (Eigen3 3.3 NO_MODULE)
include(UseJava)


SET(NATIVE_LIB_SOURCES 
    ./src/cpp/MiniQbtWrapper.cpp

)


include_directories(${JNI_INCLUDE_DIRS} )
add_library(JavaMiniQbtWrapper SHARED ${NATIVE_LIB_SOURCES})

target_link_libraries(JavaMiniQbtWrapper ${JNI_LIBRARIES} Eigen3::Eigen )

SET(JAVA_LIB_SOURCES
    ./src/java/Globals.java
    ./src/java/QasmAsyncInterpreter.java
)

add_jar(
    jMiniQbt 
    SOURCES ${JAVA_LIB_SOURCES}
    ENTRY_POINT nl.hvanderheijden.miniqbt
)

add_dependencies(jMiniQbt JavaMiniQbtWrapper)

