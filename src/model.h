
#ifndef GUI_GRAPHS_WINDOW_H
#define GUI_GRAPHS_WINDOW_H

#include <memory>

#include <SFML/Graphics.hpp>


struct Node 
{
    sf::CircleShape shape;
    bool isIndicated;
};


class Model
{
public:
    Model() = default;

    void createCircle(float radius);
    std::vector<Node>& getNodes();

private:
    std::vector<Node> nodes;
};

#endif 

