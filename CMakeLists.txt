cmake_minimum_required(VERSION 3.4...3.18)

project(cppcore)

set(VCPKG_HOST_TRIPLET $ENV{VCPKG_HOST_TRIPLET})

set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)
message(STATUS "pybind11 found: ${pybind11_FOUND}")

find_package(Eigen3 CONFIG REQUIRED)
message(STATUS "Eigen3 found: ${Eigen3_FOUND}")

pybind11_add_module(cppcore src/cpp/main.cpp)

include_directories(
    "${CMAKE_SOURCE_DIR}/src/cpp"
    "${CMAKE_SOURCE_DIR}/vcpkg_installed/${VCPKG_HOST_TRIPLET}/include/eigen3"
)
target_link_libraries(cppcore PRIVATE Eigen3::Eigen)

target_compile_definitions(
    cppcore
    PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO}
)
