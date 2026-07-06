    cmake_minimum_required(VERSION 3.10)
    project(DSARefresh)

    # use modern C++17
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    # Tell CMake to compile main.cpp and matrix.cpp into an executable named "main"
    add_executable(main main.cpp matrix.cpp)
    
    # Unit Tests Executable
    add_executable(run_tests tests.cpp matrix.cpp)
