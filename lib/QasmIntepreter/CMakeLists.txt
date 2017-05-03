


SET(LIB_SOURCES 
    src/QasmAsyncIntepreter.cpp
    src/Tokens.cpp
    src/TokenVisitor.cpp
    src/TokenParser.cpp
    src/ClassicRegister.cpp
)

include_directories(${miniQbt_SOURCE_DIR}/QasmIntepreter/include)
set(LIBRARY_NAME QasmIntepreter)
add_library(${LIBRARY_NAME} STATIC ${LIB_SOURCES})
target_link_libraries(${LIBRARY_NAME} Eigen3::Eigen)

