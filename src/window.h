
#ifndef STRUCTURES_GUI_WINDOW_H
#define STRUCTURES_GUI_WINDOW_H

#include <memory>

#include <SFML/Graphics.hpp>


class Window
{
public:
    Window();

    void run();

    void drawCircle(float radius, float x_pos, float y_pos);

private:
    std::unique_ptr<sf::RenderWindow> window;
    std::vector<sf::CircleShape> shapes;
};

#endif

