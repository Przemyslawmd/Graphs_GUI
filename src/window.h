
#ifndef GUI_GRAPHS_WINDOW_H
#define GUI_GRAPHS_WINDOW_H

#include <memory>
#include <string>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "graphclient.h"

#include "client.h"
#include "gui/lines.h"
#include "gui/menu.h"
#include "graph/model.h"
#include "services/hold.h"


class Window
{
public:
    Window();

    void init();
    void run();

private:
    void resize();
    void setMessage(const std::string& message);

    void handleMousePress();
    void handleMouseRelease();
    void handleMouseMove(const sf::Event::MouseMoved*);

    void invokeAction(Action);

    void createNode();
    void removeNodes();
    void removeGraph();
    void createConnection();
    void removeConnection();
    void traverseBFS();
    void traverseDFS();
    void shortestPath();
    void minSpanningTree();
    void saveGraph();
    void readGraph();

    void callClientBFS(char key);
    void callClientDFS(char key);
    void callClientShortestPath(char src, char dst);
    void callClientMinSpanningTree();

    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<Menu> menu;
    std::unique_ptr<Lines> lines;
    std::unique_ptr<Model> model;
    std::unique_ptr<Client> client;
    std::unique_ptr<Hold> hold;
    std::unique_ptr<sf::Text> message;
};

#endif 

