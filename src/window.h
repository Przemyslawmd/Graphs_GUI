
#ifndef GUI_GRAPHS_WINDOW_H
#define GUI_GRAPHS_WINDOW_H

#include <memory>
#include <optional>
#include <tuple>

#include <SFML/Graphics.hpp>

#include "button.h"
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
    void prepareMessageArea();
    void prepareGraphArea();
    
    void resize();
    void resizeMessageArea(const sf::Vector2u& newSize);
    void resizeGraphArea(const sf::Vector2u& newSize);

    void handleMousePress();
    void handleMouseRelease();
    void handleMouseMove(const std::optional<sf::Event> event);

    std::tuple<int, float, float> isMouseOverNode(const sf::Vector2i& position);

    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<Model> model;
    std::unique_ptr<Hold> hold;

    std::vector<Button> buttons;

    sf::RectangleShape messageArea;
    std::vector<sf::Text> messages;
    std::vector<sf::RectangleShape> graphArea;

    sf::Font font;
};

#endif 

