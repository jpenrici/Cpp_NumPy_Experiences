cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

project(Cpp_NumPy_Experiences LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) 

# Configure environment for using Numpy
include(PythonEnvSetup.cmake)

# pybind11 library
find_package(pybind11 CONFIG REQUIRED)

if (NOT pybind11_FOUND)
    message(FATAL_ERROR "Library pybind11 not found! Check your installation!")
endif()

# Examples
add_subdirectory(Cpp_NumPy_Basic)
