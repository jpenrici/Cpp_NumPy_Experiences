cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

project(Cpp_NumPy_Basic LANGUAGES CXX)

set(PROGRAM_NAME test_basic)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) 

# C++ Executable
include_directories(include)

set(SOURCES
    src/example.cpp
    src/main.cpp
)

add_executable(${PROGRAM_NAME} ${SOURCES})

target_include_directories(${PROGRAM_NAME}
    PRIVATE
        ${Python3_INCLUDE_DIRS}
        ${NUMPY_INCLUDE_DIR}
)

target_link_libraries(${PROGRAM_NAME}
    PRIVATE
        Python3::Python
)
