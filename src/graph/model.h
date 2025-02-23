
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

    std::tuple<Message, std::optional<char>> createNode(const sf::Text&);
    void createNodeFromFile(char key, size_t posX, size_t posY);
    std::vector<NodeGui>& getNodes();

    std::optional<char> getSelectedNode();
    std::tuple<std::optional<char>, std::optional<char>> getTwoSelectedNodes();

    std::tuple<Message, std::optional<ConnectionData>> createConnection(const sf::Text&);
    void createConnectionFromFile(char src, char dst, size_t weight);
    std::vector<Connection>& getConnections();
    void moveNodeConnections(char key);
    std::tuple<Message, std::optional<char>, std::optional<char>> removeConnection();

    void colorPath(const std::vector<char>& path);
    void colorEdges(const std::vector<std::tuple<char, char>>& edges);
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

