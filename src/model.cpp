
#include "model.h"

constexpr size_t initialNodeX = 10;
constexpr size_t initialNodeY = 30;


std::vector<Node>& Model::getNodes()
{
    return nodes;
}


void Model::createCircle(float radius)
{
    auto& node = nodes.emplace_back(Node{ sf::CircleShape{ radius, 100 }, false });
    node.shape.setPosition({ initialNodeX, initialNodeY });
    node.shape.setFillColor({ 51, 153, 255 });
}