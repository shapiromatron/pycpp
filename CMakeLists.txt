cmake_minimum_required(VERSION 3.4...3.18)

project(cppcore)

set(VCPKG_HOST_TRIPLET $ENV{VCPKG_HOST_TRIPLET})

set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)
message(STATUS "pybind11 found: ${pybind11_FOUND}")

set(EIGEN_PATH "${CMAKE_SOURCE_DIR}/vcpkg_installed/${VCPKG_HOST_TRIPLET}/include")
message(STATUS "Eigen path: ${EIGEN_PATH}")

pybind11_add_module(cppcore src/cpp/main.cpp)

include_directories(${CMAKE_SOURCE_DIR}/src/cpp ${EIGEN_PATH})

target_compile_definitions(
    cppcore
    PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO}
)
