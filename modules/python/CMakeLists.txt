cmake_minimum_required (VERSION 3.5)
project(PyMiniQbt)
set (
	python_version 3.5.0
)
find_package(PythonInterp ${python_version} REQUIRED)
find_package(PythonLibs ${python_version} REQUIRED)
find_package (Eigen3 3.3 NO_MODULE)

if (PYTHONINTERP_FOUND)
    set(SETUP_PY_IN "${CMAKE_CURRENT_SOURCE_DIR}/setup.py")
    set(SETUP_PY    "${CMAKE_CURRENT_BINARY_DIR}/setup.py")
    set(OUTPUT      "${CMAKE_CURRENT_BINARY_DIR}/build")
   
    set(
      PyMiniQbt_SOURCE_FILES
      ${CMAKE_CURRENT_SOURCE_DIR}/MiniQbt.cpp
    )

	if(WIN32)
		set(
			PyMiniQbt_LIB
			${MiniQbt_BINARY_DIR}/x64/Debug
		)
	else()
		set(
			PyMiniQbt_LIB
			${MiniQbt_BINARY_DIR}
		)
	endif()
	


    configure_file(${SETUP_PY_IN} ${SETUP_PY})

    add_custom_command(OUTPUT ${OUTPUT}
                       COMMAND ${PYTHON_EXECUTABLE} ${SETUP_PY} build
                       COMMAND ${CMAKE_COMMAND} -E touch ${OUTPUT}
                       )

    add_custom_target(PyMiniQbt ALL DEPENDS ${OUTPUT})


  add_test(NAME pyNativeTests COMMAND ${PYTHON_EXECUTABLE} ${PyMiniQbt_SOURCE_DIR}/tests/native_tests_without_allocating.py)
  add_test(NAME pyThreadedTests COMMAND ${PYTHON_EXECUTABLE} ${PyMiniQbt_SOURCE_DIR}/tests/multi_threaded_tests.py)
#  COMMAND ${CMAKE_CURRENT_BINARY_DIR}/IntepreterTests)
  install(CODE "execute_process(COMMAND ${PYTHON_EXECUTABLE} ${SETUP_PY} install)")
endif()