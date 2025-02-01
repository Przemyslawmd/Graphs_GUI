cmake_minimum_required(VERSION 3.16)
project(SFML_TEST)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)

configure_file(${PROJECT_SOURCE_DIR}/src/config.h.in ${PROJECT_SOURCE_DIR}/src/config.h)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(SFML_TEST 
    "src/main.cpp"
    "src/window.cpp"
    "src/graph/model.cpp"
    "src/widgets/input.cpp"
    "src/widgets/button.cpp")

target_link_libraries(SFML_TEST PRIVATE SFML::Graphics)
