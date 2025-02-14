cmake_minimum_required(VERSION 3.25)
project(GraphsGui)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

option(BUILD_TESTS "Build tests" ON)

add_subdirectory(src)
if (BUILD_TESTS MATCHES ON)
    add_subdirectory(test)
endif()
