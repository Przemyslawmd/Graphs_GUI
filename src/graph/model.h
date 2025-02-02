
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

    void createNode(sf::Font&, const std::string&);
    std::vector<Node>& getNodes();

    Message createConnection();
    void moveConnection(size_t index);
    std::vector<Connection>& getConnections();

    void removeAll();

    std::tuple<int, float, float> isMouseOverNode(const sf::Vector2i& position);

private:
    std::vector<Node> nodes;
    std::vector<Connection> connections;
};

#endif 

