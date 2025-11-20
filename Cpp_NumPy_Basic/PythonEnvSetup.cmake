# Configure environment for using Numpy

set(VENV_DIR "${CMAKE_SOURCE_DIR}/.venv")

if (UNIX OR APPLE)
    set(PYTHON_BOOTSTRAP "python3")
elseif (WIN32)
    set(PYTHON_BOOTSTRAP "python")
endif()

if (NOT EXISTS "${VENV_DIR}")
    message(STATUS "Creating Python virtual environment .venv ...")

    if (UNIX OR APPLE)
        execute_process(
            COMMAND bash -c "${PYTHON_BOOTSTRAP} -m venv \"${VENV_DIR}\""
            RESULT_VARIABLE VENV_CREATE_RESULT
            ERROR_VARIABLE  VENV_CREATE_ERROR
        )
    elseif (WIN32)
        execute_process(
            COMMAND powershell.exe -Command "& { ${PYTHON_BOOTSTRAP} -m venv '${VENV_DIR}' }"
            RESULT_VARIABLE VENV_CREATE_RESULT
            ERROR_VARIABLE  VENV_CREATE_ERROR
        )
    endif()

    if (NOT VENV_CREATE_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to create .venv: ${VENV_CREATE_ERROR}")
    endif()

    message(STATUS ".venv created successfully.")
else()
    message(STATUS ".venv already exists.")
endif()

#  Define paths inside the venv
if (UNIX OR APPLE)
    set(PYTHON_EXECUTABLE "${VENV_DIR}/bin/python")
    set(PIP_EXECUTABLE     "${VENV_DIR}/bin/pip")
elseif (WIN32)
    set(PYTHON_EXECUTABLE "${VENV_DIR}/Scripts/python.exe")
    set(PIP_EXECUTABLE     "${VENV_DIR}/Scripts/pip.exe")
endif()

#  Ensure CMake finds THIS Python, not system
set(Python3_EXECUTABLE "${PYTHON_EXECUTABLE}")

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

# NumPy
execute_process(
    COMMAND ${PIP_EXECUTABLE} show numpy
    RESULT_VARIABLE NUMPY_CHECK_RESULT
)

if (NOT NUMPY_CHECK_RESULT EQUAL 0)
    message(STATUS "NumPy not found — installing ...")
    execute_process(
        COMMAND ${PIP_EXECUTABLE} install numpy
        RESULT_VARIABLE NUMPY_INSTALL_RESULT
        ERROR_VARIABLE NUMPY_INSTALL_ERROR
    )
    if (NOT NUMPY_INSTALL_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to install NumPy: ${NUMPY_INSTALL_ERROR}")
    endif()
    message(STATUS "NumPy installed successfully.")
else()
    message(STATUS "NumPy already present in .venv.")
endif()

#  Get NumPy include dir for C++ compilation
execute_process(
    COMMAND ${PYTHON_EXECUTABLE} -c "import numpy; print(numpy.get_include())"
    OUTPUT_VARIABLE NUMPY_INCLUDE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

set(NUMPY_INCLUDE_DIR "${NUMPY_INCLUDE_DIR}" CACHE INTERNAL "NumPy include directory")

message(STATUS "NumPy include dir: ${NUMPY_INCLUDE_DIR}")
message(STATUS "Python environment ready.")
