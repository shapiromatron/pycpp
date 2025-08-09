cmake_minimum_required(VERSION 3.4...3.18)

project(cppcore)

set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)
message(STATUS "pybind11 found: ${pybind11_FOUND}")

pybind11_add_module(cppcore src/cpp/main.cpp)

target_compile_definitions(
    cppcore
    PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO}
)
