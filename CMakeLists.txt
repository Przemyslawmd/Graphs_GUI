cmake_minimum_required(VERSION 3.20)
project(GRAPHS_GUI)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)

configure_file(${PROJECT_SOURCE_DIR}/src/config.h.in ${PROJECT_SOURCE_DIR}/src/config.h)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)

FetchContent_Declare(Graphs
    GIT_REPOSITORY https://github.com/Przemyslawmd/Graphs.git
    GIT_TAG main)

FetchContent_MakeAvailable(SFML Graphs)

add_executable(GraphsGui 
    "src/main.cpp"
    "src/client.cpp"
    "src/window.cpp"
    "src/graph/connection.cpp"
    "src/graph/model.cpp"
    "src/graph/node.cpp"
    "src/services/iofile.cpp"
    "src/services/keys.cpp"
    "src/gui/input.cpp"
    "src/gui/button.cpp"
    "src/gui/lines.cpp"
    "src/gui/menu.cpp"
    "src/gui/radio.cpp")

target_include_directories(
    GraphsGui 
    PRIVATE 
    GraphsLib 
    "src")

target_link_libraries(GraphsGui PRIVATE SFML::Graphics GraphsLib)
