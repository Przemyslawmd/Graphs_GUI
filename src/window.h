
#ifndef GUI_GRAPHS_WINDOW_H
#define GUI_GRAPHS_WINDOW_H

#include <map>
#include <memory>
#include <optional>
#include <tuple>

#include <SFML/Graphics.hpp>

#include "button.h"
#include "defines.h"
#include "input.h"
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
    void setLinesPositions(const sf::Vector2u& size);

    void resize();
    void resizeLines(const sf::Vector2u& size);

    void setMessage(const std::string& message);

    void handleMousePress();
    void handleMouseRelease();
    void handleMouseMove(const std::optional<sf::Event> event);

    std::tuple<int, float, float> isMouseOverNode(const sf::Vector2i& position);

    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<Model> model;
    std::unique_ptr<Hold> hold;
    std::unique_ptr<sf::Text> message;

    std::vector<Button> buttons;
    std::map<Indicator, Input> inputs;
    std::map<Line, sf::RectangleShape> lines;

    sf::Font font;
};

#endif 

