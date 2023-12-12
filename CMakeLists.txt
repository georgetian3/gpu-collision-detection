cmake_minimum_required(VERSION 3.5)
project(gpu-collision-detection)
set(CMAKE_CXX_STANDARD 17)

option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_BUILD_DOCS OFF)
add_subdirectory(libs/glfw)

set(OpenCL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/OpenCL-Headers)
find_package(OpenCL)

option(BUILD_DOCS "Build Documentation" OFF)
option(BUILD_EXAMPLES "Build Examples" OFF)
option(OPENCL_CLHPP_BUILD_TESTING "Enable support for OpenCL C++ headers testing." OFF)

add_subdirectory(libs/OpenCL-Headers)
add_subdirectory(libs/OpenCL-CLHPP)
add_subdirectory(libs/opencl-icd-loader)

set_target_properties(OpenCL PROPERTIES FOLDER "opencl-icd-loader")
set_target_properties(cllayerinfo PROPERTIES FOLDER "opencl-icd-loader")
set(OpenCL_LIBRARIES OpenCL)
include_directories(${OpenCL_INCLUDE_DIR})


# if (MSVC)
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
# else()
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++17")
#     if(NOT WIN32)
#         set(GLAD_LIBRARIES dl)
#     endif()
# endif()

include_directories(
    headers/
    shaders/
    libs/glad/include/
    libs/glfw/include/
    libs/glm/
    libs/imgui/
    libs/imgui/backends/
    libs/stb/
    libs/OpenCL-CLHPP/include/
)

file(GLOB LIBS_SOURCES
    libs/glad/src/glad.c
    libs/imgui/*.cpp
    libs/imgui/backends/*.cpp
)
file(GLOB PROJECT_HEADERS headers/*.hpp)
file(GLOB_RECURSE PROJECT_SOURCES sources/*.cpp)

add_definitions(-DGLFW_INCLUDE_NONE)

add_executable(
    ${PROJECT_NAME}
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
    ${LIBS_SOURCES}
)

target_link_libraries(
    ${PROJECT_NAME}
    OpenCL::OpenCL
    glfw
    ${GLFW_LIBRARIES}
    ${GLAD_LIBRARIES}
)

# set_target_properties(${PROJECT_NAME} PROPERTIES 
#     LINK_FLAGS "/ENTRY:mainCRTStartup /SUBSYSTEM:WINDOWS")

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
    DEPENDS ${RESOURCES}
)
