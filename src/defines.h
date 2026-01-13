
#ifndef GUI_GRAPHS_DEFINES_H
#define GUI_GRAPHS_DEFINES_H

#include <cstddef>


constexpr float MARGIN_X = 20.f;
constexpr float MARGIN_UP_GRAPHS = 70.f;
constexpr float MARGIN_BOTTOM_GRAPHS = 80.f;

constexpr float MESSAGE_AREA_HEIGHT = 40.f;
constexpr float MESSAGES_UP = 60.f;
constexpr float MESSAGES_MARGIN_BOTTOM = 20.f;

constexpr size_t MAX_NODES = 30;

constexpr float NODE_RADIUS = 20.f;


enum class Line 
{
    GRAPHS_UP,
    GRAPHS_BOTTOM,
    GRAPHS_RIGHT,
    GRAPHS_LEFT,
    MESSAGE_UP,
    MESSAGE_BOTTOM,
    MESSAGE_LEFT,
    MESSAGE_RIGHT,
};


enum class Action
{
    COLOR,
    CONNECTION_ADD,
    CONNECTION_INPUT,
    CONNECTION_REMOVE,
    FILE_INPUT,
    MIN_SPANNING_TREE,
    NODE_ADD,
    NODE_INPUT,
    NODE_REMOVE,
    READ_GRAPH,
    REMOVE_ALL,
    RADIO_DIRECTED,
    RADIO_UNDIRECTED,
    RESET_COLOR,
    RESET_PATH,
    RESET_TREE,
    SAVE_GRAPH,
    SHORTEST_PATH,
    TRAVERSE_BFS,
    TRAVERSE_DFS,

    NO_ACTION
};

#endif

