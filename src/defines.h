
#ifndef GUI_GRAPHS_DEFINES_H
#define GUI_GRAPHS_DEFINES_H


constexpr int DEFAULT_WINDOW_WIDTH = 1600;
constexpr int DEFAULT_WINDOW_HEIGHT = 900;

constexpr float MARGIN_X = 20.f;
constexpr float MARGIN_UP_GRAPHS = 50.f;
constexpr float MARGIN_BOTTOM_GRAPHS = 80.f;

constexpr float MESSAGE_AREA_HEIGHT = 40.f;
constexpr float MESSAGE_AREA_BOTTOM_DISTANCE = 60.f;

constexpr float MESSAGE_X = 30.f;
constexpr float MESSAGE_BOTTOM_DISTANCE = 50.f;


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


#endif

