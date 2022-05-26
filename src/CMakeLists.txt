cmake_minimum_required(VERSION 3.0.0)
project(opengl-test VERSION 0.1.0)

add_executable(${PROJECT_NAME}
    main.cpp
    test_util.cpp
    test_window.cpp
    test_triangle.cpp
)

target_link_libraries(${PROJECT_NAME} ${dependLib})