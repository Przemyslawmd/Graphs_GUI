
#ifndef GUI_GRAPHS_DEFINES_H
#define GUI_GRAPHS_DEFINES_H


constexpr float MARGIN_X = 20.f;
constexpr float MARGIN_UP_GRAPHS = 50.f;
constexpr float MARGIN_BOTTOM_GRAPHS = 80.f;

constexpr float MESSAGE_AREA_HEIGHT = 40.f;
constexpr float MESSAGES_UP = 60.f;
constexpr float MESSAGES_MARGIN_BOTTOM = 20.f;

constexpr size_t MAX_NODES = 30;

constexpr size_t RED = 51;
constexpr size_t GREEN = 153;
constexpr size_t BLUE = 255;


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
    NODE_ADD,
    NODE_REMOVE,
    NODE_INPUT,
    CONNECTION_ADD,
    CONNECTION_INPUT,
    REMOVE_ALL,
    TRAVERSE_BFS,
    TRAVERSE_DFS,
    SHORTEST_PATH,
    RESET_PATH,
};


#endif

