
#ifndef GUI_GRAPHS_MODEL_H
#define GUI_GRAPHS_MODEL_H

#include <memory>

#include <SFML/Graphics.hpp>

#include "message.h"


struct Node 
{
    sf::CircleShape shape;
    size_t index;
    bool isIndicated;
    std::vector<size_t> connections;
};


struct Connection 
{
    sf::RectangleShape line;
    size_t node_1;
    size_t node_2;
};


class Model
{
public:
    Model() = default;

    void createNode(float radius);
    std::vector<Node>& getNodes();

    Message createConnection();
    void moveConnection(size_t index);
    std::vector<Connection>& getConnections();

    void removeAll();

private:
    std::vector<Node> nodes;
    std::vector<Connection> connections;
};

#endif 

