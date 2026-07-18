ke_minimum_required(VERSION 3.10)

add_library(MySTL
    vector.h
    pair.h 
    list.h 
    forward_list.h 
    stack.h 
    queue.h 
    unordered_map.h
    matrix.h
    matrix.cpp
    algorithm.h
)

# Add an alias target so that it can be linked as MySTL::MySTL
# This makes it consistent with using find_package() in other projects
add_library(MySTL::MySTL ALIAS MySTL)

target_include_directories(MySTL PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
