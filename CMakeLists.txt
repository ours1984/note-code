cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 11)

# set dir
set(nodeOutDir ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(gladIncDir ${CMAKE_CURRENT_SOURCE_DIR}/third/glad)
set(gtestIncDir ${CMAKE_CURRENT_SOURCE_DIR}/third/googletest/googletest/include)
set(glfwIncDir ${CMAKE_CURRENT_SOURCE_DIR}/third/glfw/include)
set(eigenIncDir ${CMAKE_CURRENT_SOURCE_DIR}/third/eigen/Eigen)
set(stbIncDir ${CMAKE_CURRENT_SOURCE_DIR}/third/stb)
set(glmIncDir ${CMAKE_CURRENT_SOURCE_DIR}/third/glm)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${nodeOutDir})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${nodeOutDir})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${nodeOutDir})
set(LIBRARY_OUTPUT_PATH ${nodeOutDir})

set(CMAKE_DEBUG_POSTFIX "_d")    
set(CMAKE_RELEASE_POSTFIX "_r") 

# inc/link dir
include_directories(${glmIncDir})
include_directories(${gladIncDir})
include_directories(${glfwIncDir})
include_directories(${gtestIncDir})
include_directories(${stbIncDir})
include_directories(${eigenIncDir})

link_directories(${nodeOutDir})


# add project
add_subdirectory(third/googletest)
add_subdirectory(third/glfw)
add_subdirectory(third/glad)

set (dependLib
    glfw
    glad
    gtest
    -lopengl32
)
add_subdirectory(opengl-note)

#enable_testing()
#include(googletest)
#find_package(gtest 1.10.0)
#gtest_discover_tests(opengl-test)

