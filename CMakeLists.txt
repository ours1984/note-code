cmake_minimum_required(VERSION 3.0.0)
project(opengl-note VERSION 0.1.0)

set(nodeOutDir ${PROJECT_SOURCE_DIR}/bin)
set(gladIncDir ${PROJECT_SOURCE_DIR}/glad)
set(flfwIncDir ${PROJECT_SOURCE_DIR}/glfw/include)

include_directories(${gladIncDir})
include_directories(${flfwIncDir})
link_directories(${nodeOutDir})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${nodeOutDir})
set(LIBRARY_OUTPUT_PATH ${nodeOutDir})

add_subdirectory(glfw)
add_subdirectory(glad)

set (dependLib
    glfw
    glad
    -lopengl32
)
add_subdirectory(window)

