
#ifndef GUI_GRAPHS_MODEL_H
#define GUI_GRAPHS_MODEL_H

#include <memory>
#include <vector>

#include "connection.h"
#include "node.h"
#include "../message.h"
#include "../services/keys.h"


class Model
{
public:
    Model();

    std::tuple<Message, std::optional<char>> createNode(sf::Font&, sf::Text&);
    std::vector<NodeGui>& getNodes();
    std::tuple<Message, std::optional<char>> getSelectedNode();

    std::tuple<Message, std::optional<char>, std::optional<char>> createConnection();
    void moveConnection(size_t index);
    std::vector<Connection>& getConnections();

    void removeAll();

    std::tuple<int, float, float> isMouseOverNode(const sf::Vector2i& position);

private:
    size_t checkSelectedNodes();

    std::vector<NodeGui> nodes;
    std::vector<Connection> connections;

    std::unique_ptr<Keys> keys;
};

#endif 

