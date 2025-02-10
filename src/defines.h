
#ifndef GUI_GRAPHS_DEFINES_H
#define GUI_GRAPHS_DEFINES_H


constexpr float MARGIN_X = 20.f;
constexpr float MARGIN_UP_GRAPHS = 50.f;
constexpr float MARGIN_BOTTOM_GRAPHS = 80.f;

constexpr float MESSAGE_AREA_HEIGHT = 40.f;
constexpr float MESSAGES_UP = 60.f;
constexpr float MESSAGES_MARGIN_BOTTOM = 20.f;

constexpr size_t MAX_NODES = 30;


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


enum class Menu
{
    NODE_ADD,
    NODE_UPDATE,
    NODE_INPUT,
    CONNECT_NODES,
    REMOVE_ALL,
    TRAVERSE_BFS,
    TRAVERSE_DFS,
};


#endif

