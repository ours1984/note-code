cmake_minimum_required(VERSION 3.0.0)

cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME dirname)

project(${dirname} VERSION 0.1.0)

find_package(benchmark REQUIRED)

set (dependLib
    benchmark::benchmark
    benchmark::benchmark_main
)

add_executable(${dirname}
    search.cpp
    sort.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${dirname} ${dependLib})

set_target_properties(${dirname} PROPERTIES DEBUG_POSTFIX "_d")
set_target_properties(${dirname} PROPERTIES RELEASE_POSTFIX "_r")  
