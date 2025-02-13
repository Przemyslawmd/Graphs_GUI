
#ifndef GUI_GRAPHS_WINDOW_H
#define GUI_GRAPHS_WINDOW_H

#include <map>
#include <memory>
#include <optional>
#include <tuple>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "graphclient.h"

#include "client.h"
#include "defines.h"
#include "graph/model.h"
#include "services/hold.h"
#include "widgets/button.h"
#include "widgets/input.h"


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
    void setInputFocus(bool, bool);

    void handleMousePress();
    void handleMouseRelease();
    void handleMouseMove(const sf::Event::MouseMoved*);
    void handleTextEntered(const const sf::Event::TextEntered*);

    void createNode();
    void removeNode();
    void removeGraph();
    void createConnection();
    void traverseBFS();
    void traverseDFS();
    void shortestPath();

    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<Model> model;
    std::unique_ptr<Client> client;
    std::unique_ptr<Hold> hold;
    std::unique_ptr<sf::Text> message;

    std::vector<Button> buttons;
    std::map<Menu, Input> inputs;
    std::map<Line, sf::RectangleShape> lines;
};

#endif 

