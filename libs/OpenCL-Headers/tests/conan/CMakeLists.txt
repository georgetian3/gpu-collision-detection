cmake_minimum_required(VERSION 3.0)
project(PackageTest C)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(OpenCLHeaders REQUIRED)

add_executable(example example.c)
target_link_libraries(example OpenCL::Headers)
