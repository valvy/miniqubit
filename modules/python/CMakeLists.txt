cmake_minimum_required (VERSION 3.5)
project(PyMiniQbt)
find_program(PYTHON "python3")
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

if (PYTHON)
    set(SETUP_PY_IN "${CMAKE_CURRENT_SOURCE_DIR}/setup.py")
    set(SETUP_PY    "${CMAKE_CURRENT_BINARY_DIR}/setup.py")
    set(OUTPUT      "${CMAKE_CURRENT_BINARY_DIR}/build")
   
    set(
      PyMiniQbt_SOURCE_FILES
      ${CMAKE_CURRENT_SOURCE_DIR}/MiniQbt.cpp
    )

    set(
      PyMiniQbt_EIGEN_INCLUDE_LIB
      ${EIGEN3_INCLUDE_DIR}
    )
    
    set(
      PyMiniQbt_LIB
      MiniQbt
    )

    configure_file(${SETUP_PY_IN} ${SETUP_PY})

    add_custom_command(OUTPUT ${OUTPUT}
                       COMMAND ${PYTHON} ${SETUP_PY} build
                       COMMAND ${CMAKE_COMMAND} -E touch ${OUTPUT}
                       DEPENDS ${DEPS})

    add_custom_target(PyMiniQbt ALL DEPENDS ${OUTPUT})


  add_test(NAME pyNativeTests COMMAND ${PYTHON} ${PyMiniQbt_SOURCE_DIR}/tests/native_tests_without_allocating.py)
  add_test(NAME pyThreadedTests COMMAND ${PYTHON} ${PyMiniQbt_SOURCE_DIR}/tests/multi_threaded_tests.py)
#  COMMAND ${CMAKE_CURRENT_BINARY_DIR}/IntepreterTests)
  install(CODE "execute_process(COMMAND ${PYTHON} ${SETUP_PY} install)")
endif()