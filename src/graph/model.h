
#ifndef GUI_GRAPHS_MODEL_H
#define GUI_GRAPHS_MODEL_H

#include <memory>
#include <vector>

#include "connection.h"
#include "node.h"
#include "message.h"
#include "services/keys.h"


class Model
{
public:
    Model();

    std::tuple<Message, std::optional<char>> createNode(sf::Text&);
    std::vector<NodeGui>& getNodes();
    std::tuple<Message, std::optional<char>> getSelectedNode();
    std::tuple<Message, std::optional<char>, std::optional<char>> getTwoSelectedNodes();

    std::tuple<Message, std::optional<ConnectionLibraryInterface>> createConnection(sf::Text&);
    std::vector<Connection>& getConnections();
    void moveNodeConnections(char key);
    std::tuple<Message, std::optional<char>, std::optional<char>> removeConnection();

    void colorPath(const std::vector<char>& path);
    void resetPath();

    std::tuple<Message, std::optional<char>> removeNode();
    void removeAll();

    std::tuple<int, float, float> isMouseOverNode(const sf::Vector2i& position);
    void checkMouseOverConnection(const sf::Vector2i& position);

private:
    void moveConnection(Connection&);
    size_t countSelectedNodes();
    size_t countSelectedConnections();

    std::vector<NodeGui> nodes;
    std::vector<Connection> connections;

    std::unique_ptr<Keys> keys;
};

#endif 

