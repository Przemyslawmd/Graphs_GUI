
#ifndef GUI_GRAPHS_MODEL_H
#define GUI_GRAPHS_MODEL_H

#include <memory>
#include <vector>

#include "connection.h"
#include "node.h"
#include "../message.h"


class Model
{
public:
    Model() = default;

    std::tuple<Message, std::optional<char>> createNode(sf::Font&, sf::Text&);
    std::vector<NodeGui>& getNodes();

    Message createConnection();
    void moveConnection(size_t index);
    std::vector<Connection>& getConnections();

    void removeAll();

    std::tuple<int, float, float> isMouseOverNode(const sf::Vector2i& position);

private:
    std::vector<NodeGui> nodes;
    std::vector<Connection> connections;
};

#endif 

