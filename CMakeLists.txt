cmake_minimum_required(VERSION 3.0.0)
project(opengl-note VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)

set(nodeOutDir ${PROJECT_SOURCE_DIR}/bin)
set(gladIncDir ${PROJECT_SOURCE_DIR}/glad)
set(gtestIncDir ${PROJECT_SOURCE_DIR}/googletest/googletest/include)
set(glfwIncDir ${PROJECT_SOURCE_DIR}/glfw/include)

include_directories(${gladIncDir})
include_directories(${glfwIncDir})
include_directories(${gtestIncDir})
link_directories(${nodeOutDir})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${nodeOutDir})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${nodeOutDir})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${nodeOutDir})
set(LIBRARY_OUTPUT_PATH ${nodeOutDir})

add_subdirectory(googletest)
add_subdirectory(glfw)
add_subdirectory(glad)

set (dependLib
    glfw
    glad
    gtest
    -lopengl32
)
add_subdirectory(src)

#enable_testing()
#include(googletest)
#find_package(gtest 1.10.0)
#gtest_discover_tests(opengl-test)

