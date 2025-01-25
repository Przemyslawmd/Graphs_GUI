
#ifndef STRUCTURES_GUI_WINDOW_H
#define STRUCTURES_GUI_WINDOW_H

#include <memory>
#include <optional>
#include <tuple>

#include <SFML/Graphics.hpp>

#include "model.h"


struct Hold
{
    bool isHeld;    // is mouse button pressed
    bool isMoved;   // is there move between mouse button press and release, to recognize click without moving
    int index;      // index of held object in its container
    float shiftX;   // distance between the mouse X position and the center of held object
    float shiftY;   // distance between the mouse Y position and the center of held object
};


class Window
{
public:
    Window();

    void init();
    void run();

    void createConnection();
    void prepareMenu();

private:

    void handleMousePress();
    void handleMouseRelease();
    void handleMouseMove(const std::optional<sf::Event> event);

    std::tuple<int, float, float> isMouseOverCircle(const sf::Vector2i& position);

    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<Model> model;

    std::vector<sf::RectangleShape> menus;
    std::vector<sf::RectangleShape> lines;
    std::vector<sf::Text> titles;

    sf::Font font;
    Hold hold;
};

#endif 

