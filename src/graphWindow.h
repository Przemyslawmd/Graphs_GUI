
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
#include "graph/tempConnection.h"
#include "services/hold.h"


class GraphWindow
{
public:
    GraphWindow();

    void init();
    void run();

private:
    void resize();
    void setMessage(const std::string& message);

    void handleMousePressLeft();
    void handleMousePressRight();

    void handleMouseReleaseLeft();
    void handleMouseReleaseRight();

    void handleMovePressLeft();
    void handleMovePressRight();
    std::tuple<bool, float, float> checkMove();

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
    void colorGraph();
    void resetColors();

    void saveGraph();
    void readGraph();

    void callBFS(char key);
    void callDFS(char key);
    void callShortestPath(char src, char dst);
    void callMinSpanningTree();
    void callColorGraph();
    void callResetColorGraph();

    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<Menu> menu;
    std::unique_ptr<Lines> lines;
    std::unique_ptr<Model> model;
    std::unique_ptr<Client> client;
    std::unique_ptr<Hold> hold;
    std::unique_ptr<sf::Text> message;
    std::unique_ptr<TempConnection> tempConnection;
};

#endif 

