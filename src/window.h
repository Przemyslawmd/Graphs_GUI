
#ifndef STRUCTURES_GUI_WINDOW_H
#define STRUCTURES_GUI_WINDOW_H

#include <memory>
#include <tuple>

#include <SFML/Graphics.hpp>


struct Hold
{
    bool isHeld;
    float shiftX;   // distance between the mouse X position and the center of shape
    float shiftY;   // distance between the mouse Y position and the center of shape
    int index;
};


class Window
{
public:
    Window();

    void init();
    void run();

    void drawCircle(float radius, float x_pos, float y_pos);
    void prepareMainMenu();
    void prepareTexts();

private:
    std::tuple<int, int, int> isMouseOverCircle(const sf::Vector2i& position);

    std::unique_ptr<sf::RenderWindow> window;
    std::vector<sf::CircleShape> shapes;
    std::vector<sf::RectangleShape> menus;
    std::vector<sf::Text> titles;

    sf::Font font;
    Hold hold;
};

#endif

