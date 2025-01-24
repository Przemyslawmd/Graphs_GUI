
#ifndef STRUCTURES_GUI_WINDOW_H
#define STRUCTURES_GUI_WINDOW_H

#include <memory>
#include <tuple>

#include <SFML/Graphics.hpp>


struct Hold
{
    bool isHeld;
    bool isMoved;   // to recognize whether after release is click action
    int index;
    float shiftX;   // distance between the mouse X position and the center of shape
    float shiftY;   // distance between the mouse Y position and the center of shape
};


struct Circle 
{
    sf::CircleShape shape;
    bool isIndicated;
};


class Window
{
public:
    Window();

    void init();
    void run();

    void createCircle(float radius);
    void prepareMenu();

private:
    std::tuple<int, float, float> isMouseOverCircle(const sf::Vector2i& position);

    std::unique_ptr<sf::RenderWindow> window;
    std::vector<Circle> circles;
    std::vector<sf::RectangleShape> menus;
    std::vector<sf::Text> titles;

    sf::Font font;
    Hold hold;
};

#endif

