cmake_minimum_required(VERSION 3.10)

project(MySTL)

# Include the library directory first
add_subdirectory(src/core/)

# Make building tests optional so that other projects including this
# library via add_subdirectory won't build the tests by default.
option(MYSTL_BUILD_TESTS "Build MySTL tests" OFF)

if(MYSTL_BUILD_TESTS)
    add_executable(mystl_tests tests.cpp)
    target_link_libraries(mystl_tests PRIVATE MySTL)
endif()
