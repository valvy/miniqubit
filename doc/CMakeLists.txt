
find_package(Doxygen)
IF(DOXYGEN_FOUND)
CONFIGURE_FILE(./doxygen.in ${CMAKE_CURRENT_BINARY_DIR}/doxygen)
add_custom_target(doc 
    COMMAND ${DOXYGEN_EXECUTABLE}  ${CMAKE_CURRENT_BINARY_DIR}/doxygen 
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM
)
ELSE(DOXYGEN_FOUND)
MESSAGE("Skipping doxygen")
ENDIF(DOXYGEN_FOUND)