cmake_minimum_required (VERSION 3.5)
project(JavaMiniQbt)


GET_DIRECTORY_PROPERTY(
    JavaNativeMiniQbt_BINARY_DIR
    DIRECTORY ../javaNativeMiniQbt 
    DEFINITION JavaNativeMiniQbt_BINARY_DIR
)

GET_DIRECTORY_PROPERTY(
    JAVA_NATIVE_LIB_NAME
    DIRECTORY ../javaNativeMiniQbt
    DEFINITION JAVA_NATIVE_LIB_NAME
)
SET(JAVA_LIB_SOURCES
    ./src/Globals.java
    ./src/QasmAsyncInterpreter.java
)  


add_jar(
    jMiniQbt 
    SOURCES ${JAVA_LIB_SOURCES} 
   # ../../../build/modules/java/javaBindings/libJavaMiniQbtWrapper.solibJavaMiniQbtWrapper

    VERSION ${miniQbt_MAJOR_VERSION}.${miniQbt_MINOR_VERSION}.${miniQbt_PATCH_VERSION}
)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin" OR ${CMAKE_SYSTEM_NAME} MATCHES "Linux" ) 
# Adding the shared objects to te jar 
MESSAGE("Adding wrapper of miniqbt to the jar")
add_custom_command(
    TARGET jMiniQbt
    POST_BUILD
    COMMAND /usr/bin/jar -uvf 
    ${JavaMiniQbt_BINARY_DIR}/jMiniQbt-${miniQbt_MAJOR_VERSION}.${miniQbt_MINOR_VERSION}.${miniQbt_PATCH_VERSION}.jar 
    lib${JAVA_NATIVE_LIB_NAME}.so
    WORKING_DIRECTORY ${JavaNativeMiniQbt_BINARY_DIR} 
)
ELSE()
MESSAGE("This platform has no proper Java support for MiniQbt.")
ENDIF()
