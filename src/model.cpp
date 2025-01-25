
#include "model.h"

#include "utils.h"


constexpr size_t initialNodeX = 10;
constexpr size_t initialNodeY = 30;
constexpr float PI = 3.14159265;


std::vector<Node>& Model::getNodes()
{
    return nodes;
}


void Model::createNode(float radius)
{
    auto& node = nodes.emplace_back(Node{ sf::CircleShape{ radius, 100 }, false });
    node.shape.setPosition({ initialNodeX, initialNodeY });
    node.shape.setFillColor({ 51, 153, 255 });
}


void Model::createConnection()
{
    std::vector<size_t> indicated;
    for (size_t i = 0; i < nodes.size(); i++) {
        if (nodes[i].isIndicated) {
            indicated.push_back(i);
        }
    }
    if (indicated.size() != 2) {
        return;
    }

    size_t index_1 = indicated[0];
    size_t index_2 = indicated[1];
    sf::Vector2f pos_1 = nodes[index_1].shape.getPosition();
    sf::Vector2f pos_2 = nodes[index_2].shape.getPosition();

    float distance_x = abs(pos_1.x - pos_2.x);
    float distance_y = abs(pos_1.y - pos_2.y);
    float length = sqrt(pow(distance_x, 2) + pow(distance_y, 2));
    auto& line = lines.emplace_back(sf::Vector2f{ length, 3 });

    float radius = nodes[index_1].shape.getRadius();
    line.setPosition({ pos_1.x + radius, pos_1.y + radius });

    float angle = atan(distance_y / distance_x) * 180 / PI;
    Quarter quarter = findQuarter(pos_1.x, pos_1.y, pos_2.x, pos_2.y);
    if (quarter == Quarter::ONE) {
        line.rotate(sf::degrees(angle));
    }
    else if (quarter == Quarter::TWO) {
        line.rotate(sf::degrees(180 - angle));
    }
    else if (quarter == Quarter::THREE) {
        line.rotate(sf::degrees(180 + angle));
    }
    else if (quarter == Quarter::FOUR) {
        line.rotate(sf::degrees(360 - angle));
    }

    line.setFillColor({ 51, 153, 255 });
}


std::vector<sf::RectangleShape>& Model::getConnections()
{
    return lines;
}