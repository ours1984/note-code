cmake_minimum_required(VERSION 3.0.0)

cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME dirname)

project(${dirname} VERSION 0.1.0)

#add_executable(${dirname})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#target_link_libraries(${dirname} ${dependLib})
#set_target_properties(${dirname} PROPERTIES DEBUG_POSTFIX "_d")
#set_target_properties(${dirname} PROPERTIES RELEASE_POSTFIX "_r")  
