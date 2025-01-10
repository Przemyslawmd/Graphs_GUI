
#ifndef STRUCTURES_GUI_WINDOW_H
#define STRUCTURES_GUI_WINDOW_H

#include <memory>

#include <SFML/Graphics.hpp>


struct Hold
{
    bool isHeld;
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
    int isMouseOverCircle(const sf::Vector2i& position);

    std::unique_ptr<sf::RenderWindow> window;
    std::vector<sf::CircleShape> shapes;
    std::vector<sf::RectangleShape> menus;
    std::vector<sf::Text> titles;

    sf::Font font;
    Hold hold;
};

#endif

