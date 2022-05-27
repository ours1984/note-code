cmake_minimum_required(VERSION 3.0.0)
project(opengl-test VERSION 0.1.0)

add_executable(${PROJECT_NAME}
    shader/shader.h
    shader/shader.cpp
    test.cpp
    test_util.h
    test_util.cpp
    test_window.cpp
    test_triangle.cpp
    test_shader.cpp

)

target_link_libraries(${PROJECT_NAME} ${dependLib})
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "_d")
set_target_properties(${PROJECT_NAME} PROPERTIES RELEASE_POSTFIX "_r")  

file(COPY ${PROJECT_SOURCE_DIR}/glsl DESTINATION ${nodeOutDir})