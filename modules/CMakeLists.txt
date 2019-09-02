add_subdirectory(core)
IF(ENABLE_PYTHON)
add_subdirectory(python)
ENDIF()

IF(ENABLE_JAVA)
add_subdirectory(java)
ENDIF()

