cmake_minimum_required(VERSION 3.0.0)

cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME dirname)

project(${dirname} VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
if (POLICY CMP0072)
  set(OpenGL_GL_PREFERENCE LEGACY)
endif()

# set dir
set(nodeOutDir ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(stbIncDir ${CMAKE_CURRENT_SOURCE_DIR}/third/stb)
set(softIncDir ${CMAKE_CURRENT_SOURCE_DIR}/third/softrender/include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${nodeOutDir})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${nodeOutDir})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${nodeOutDir})
set(LIBRARY_OUTPUT_PATH ${nodeOutDir})

set(CMAKE_DEBUG_POSTFIX "_d")    
set(CMAKE_RELEASE_POSTFIX "_r") 

# inc/link dir
include_directories(${stbIncDir})
include_directories(${softIncDir})
link_directories(${nodeOutDir})

# add project
add_subdirectory(third/softrender)
add_subdirectory(opengl-note)
add_subdirectory(grokking-note)
#add_subdirectory(games101-note)

#enable_testing()
#include(googletest)
#find_package(gtest 1.10.0)
#gtest_discover_tests(opengl-test)

