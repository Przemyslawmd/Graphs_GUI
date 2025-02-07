
#ifndef GUI_GRAPHS_WINDOW_H
#define GUI_GRAPHS_WINDOW_H

#include <map>
#include <memory>
#include <optional>
#include <tuple>

#include <SFML/Graphics.hpp>

#include "defines.h"
#include "graph/model.h"
#include "hold.h"
#include "widgets/button.h"
#include "widgets/input.h"

#include "graphclient.h"

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
    void handleTextEntered(const std::optional<sf::Event> event);

    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<Model> model;
    std::unique_ptr<Hold> hold;
    std::unique_ptr<sf::Text> message;

    std::vector<Button> buttons;
    std::map<Menu, Input> inputs;
    std::map<Line, sf::RectangleShape> lines;

    sf::Font font;
};

#endif 

