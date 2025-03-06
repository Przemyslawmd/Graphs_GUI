
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
    std::unique_ptr<std::vector<char>> removeNodes();

    std::tuple<Message, std::optional<ConnectionData>> createConnection(const sf::Text&);
    void createConnectionFromFile(char src, char dst, size_t weight);
    std::unique_ptr<std::vector<std::tuple<char, char>>> removeConnections();

    std::vector<NodeGui>& getNodes();
    std::optional<char> getSelectedNodeKey();
    std::tuple<std::optional<char>, std::optional<char>> getTwoSelectedNodesKeys();
    std::vector<Connection>& getConnections();

    void moveNodeConnections(char key);

    void colorPath(const std::vector<char>& path);
    void colorEdges(const std::vector<std::tuple<char, char>>& edges);
    void resetPath();

    void removeAll();

    std::tuple<int, float, float> isMouseOverNode(const sf::Vector2i& position);
    void isMouseOverConnection(const sf::Vector2i& position);

    void setDirected(bool isDirected);
    bool isDirected() const; 

private:
    void moveConnection(Connection&);
    size_t countSelectedNodes();
    bool isTypeChanged();

    std::vector<NodeGui> nodes;
    std::vector<Connection> connections;

    std::unique_ptr<Keys> keys;

    bool directed;
};

#endif 

