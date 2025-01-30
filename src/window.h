
#ifndef GUI_GRAPHS_WINDOW_H
#define GUI_GRAPHS_WINDOW_H

#include <map>
#include <memory>
#include <optional>
#include <tuple>

#include <SFML/Graphics.hpp>

#include "button.h"
#include "defines.h"
#include "model.h"
#include "hold.h"


class Window
{
public:
    Window();

    void init();
    void run();

private:
    void prepareMenu();
    void prepareLines();

    void resize();
    void resizeLines(const sf::Vector2u& newSize);

    void handleMousePress();
    void handleMouseRelease();
    void handleMouseMove(const std::optional<sf::Event> event);

    std::tuple<int, float, float> isMouseOverNode(const sf::Vector2i& position);

    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<Model> model;
    std::unique_ptr<Hold> hold;

    std::vector<Button> buttons;
    std::map<Line, sf::RectangleShape> lines;

    std::vector<sf::Text> messages;
    sf::Font font;
};

#endif 

