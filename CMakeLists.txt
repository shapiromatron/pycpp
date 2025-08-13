cmake_minimum_required(VERSION 3.4...3.18)


# required to find dependencies
if(NOT DEFINED ENV{VCPKG_HOST_TRIPLET})
    message(FATAL_ERROR "Environment variable 'VCPKG_HOST_TRIPLET' is not set")
endif()

project(cppcore)

set(VCPKG_HOST_TRIPLET $ENV{VCPKG_HOST_TRIPLET})

set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)
message(STATUS "pybind11 found: ${pybind11_FOUND}")

message(STATUS "vcpkg Triplet: ${VCPKG_HOST_TRIPLET}")
set(EIGEN_PATH "${CMAKE_SOURCE_DIR}/vcpkg_installed/${VCPKG_HOST_TRIPLET}/include")
message(STATUS "Eigen Path: ${EIGEN_PATH}")

set(GSL_DIR "${CMAKE_SOURCE_DIR}/vcpkg_installed/${VCPKG_HOST_TRIPLET}")
message(STATUS "GSL Path: ${GSL_DIR}")
set(GSL_INCLUDE_DIR "${GSL_DIR}/include")
set(GSL_LIBRARY_DIR "${GSL_DIR}/lib")
find_library(GSL_LIB gsl PATHS "${GSL_LIBRARY_DIR}")
find_library(GSLCBLAS_LIB gslcblas PATHS "${GSL_LIBRARY_DIR}")

set(NLOPT_DIR "${CMAKE_SOURCE_DIR}/vcpkg_installed/${VCPKG_HOST_TRIPLET}")
message(STATUS "NLOPT Path: ${NLOPT_DIR}")
set(NLOPT_DIR_INCLUDE_DIR "${NLOPT_DIR}/include")
set(NLOPT_DIR_LIBRARY_DIR "${NLOPT_DIR}/lib")
find_library(NLOPT_LIB nlopt PATHS "${NLOPT_DIR_LIBRARY_DIR}")

pybind11_add_module(cppcore src/cpp/main.cpp)

target_include_directories(cppcore PRIVATE ${CMAKE_SOURCE_DIR}/src/cpp)
target_include_directories(cppcore PRIVATE ${EIGEN_PATH})
target_include_directories(cppcore PRIVATE ${GSL_INCLUDE_DIR})
target_include_directories(cppcore PRIVATE ${NLOPT_DIR_INCLUDE_DIR})

target_link_libraries(cppcore PRIVATE ${NLOPT_LIB})
target_link_libraries(cppcore PRIVATE ${GSL_LIB})
target_link_libraries(cppcore PRIVATE ${GSLCBLAS_LIB})

target_compile_definitions(cppcore)
