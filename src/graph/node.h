
#ifndef GUI_GRAPHS_NODE_H
#define GUI_GRAPHS_NODE_H

#include <time.h>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>


struct NodeData
{
    char key;
    size_t posX;
    size_t posY;
};


class NodeGui : public sf::Drawable
{
public:
    NodeGui(char key);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setPosition(const sf::Vector2f& position);
    float getPositionX() const;
    float getPositionY() const;
    sf::Vector2f& getPosition() const;

    void changeSelect();

    sf::CircleShape circle;
    sf::Text text;
    char key;
    bool selected;
    time_t selectTime;
};

#endif

