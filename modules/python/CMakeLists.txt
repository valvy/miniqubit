cmake_minimum_required (VERSION 3.5)
project(PyMiniQbt)
set (CMAKE_CXX_STANDARD 14)
set (
	python_version 2.7.0
)
MESSAGE("Setting up python using ${python_version}")

find_package(Boost 1.58 COMPONENTS python REQUIRED)



find_package(PythonInterp ${python_version} REQUIRED)
find_package(PythonLibs ${python_version} REQUIRED)
find_package (Eigen3 3.3 NO_MODULE)

# Make sure we got the provided includes from miniqbt source
GET_DIRECTORY_PROPERTY(
    MINIQBT_INCLUDE_DIRS 
    DIRECTORY ${CMAKE_SOURCE_DIR}/modules/core 
    DEFINITION MINIQBT_INCLUDE_DIRS  
)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS} ${MINIQBT_INCLUDE_DIRS} )
LINK_LIBRARIES(Eigen3::Eigen ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} MiniQbt)
PYTHON_ADD_MODULE(PyMiniQbt src/PyMiniQbt.cpp)

