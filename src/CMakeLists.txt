
configure_file(${PROJECT_SOURCE_DIR}/src/config.h.in ${PROJECT_SOURCE_DIR}/src/config.h)

include(FetchContent)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)

FetchContent_Declare(Graphs
    GIT_REPOSITORY https://github.com/Przemyslawmd/Graphs.git
    GIT_TAG main)

FetchContent_MakeAvailable(SFML Graphs)

add_executable(GraphsApp 
    "main.cpp"
    "client.cpp"
    "window.cpp"
    "graph/model.cpp"
    "services/keys.cpp"
    "widgets/input.cpp"
    "widgets/button.cpp")

target_include_directories(
    GraphsApp 
    PUBLIC 
    GraphsLib 
    ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(GraphsApp PUBLIC SFML::Graphics GraphsLib)
