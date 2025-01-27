
#include "model.h"

#include "utils.h"


constexpr size_t INITIAL_NODE_X = 10;
constexpr size_t INITIAL_NODE_Y = 30;


void Model::createNode(float radius)
{
    auto& node = nodes.emplace_back( radius );
    node.circle.setPosition({ INITIAL_NODE_X, INITIAL_NODE_Y });
    node.circle.setFillColor({ 51, 153, 255 });
    node.index = nodes.size() - 1;
}


std::vector<Node>& Model::getNodes()
{
    return nodes;
}


Message Model::createConnection()
{
    std::vector<size_t> indicated;
    for (size_t i = 0; i < nodes.size(); i++) {
        if (nodes[i].isIndicated) {
            indicated.push_back(i);
        }
    }
    if (indicated.size() != 2) {
        return Message::NODES_COUNT_CONNECTION_ERROR;
    }

    size_t node_1 = indicated[0];
    size_t node_2 = indicated[1];
    sf::Vector2f pos_1 = nodes[node_1].circle.getPosition();
    sf::Vector2f pos_2 = nodes[node_2].circle.getPosition();
    float length  = calculateConnectionLength(pos_1, pos_2);

    auto& connection = connections.emplace_back( length, node_1, node_2 );

    float radius = nodes[node_1].circle.getRadius();
    connection.line.setPosition({ pos_1.x + radius, pos_1.y + radius });

    float angle = calculateConnectionAngle(pos_1, pos_2);
    connection.line.rotate(sf::degrees(angle));
    connection.line.setFillColor({ 51, 153, 255 });

    size_t connection_index = connections.size() - 1;
    nodes[node_1].connections.push_back(connection_index);
    nodes[node_2].connections.push_back(connection_index);
    return Message::OK;
}


void Model::moveConnection(size_t index)
{
    size_t node_1 = connections[index].node_1;
    size_t node_2 = connections[index].node_2;
 
    sf::Vector2f pos_1 = nodes[node_1].circle.getPosition();
    sf::Vector2f pos_2 = nodes[node_2].circle.getPosition();
    float length  = calculateConnectionLength(pos_1, pos_2);

    auto& connectionLine = connections[index].line;
    connectionLine.setSize({ length, 3 });

    float radius = nodes[node_1].circle.getRadius();
    connectionLine.setPosition({ pos_1.x + radius, pos_1.y + radius });

    float angle = calculateConnectionAngle(pos_1, pos_2);
    connectionLine.setRotation(sf::degrees(angle));
}


std::vector<Connection>& Model::getConnections()
{
    return connections;
}


void Model::removeAll()
{
    nodes.clear();
    connections.clear();
}

