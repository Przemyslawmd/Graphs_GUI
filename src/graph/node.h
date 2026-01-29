
#ifndef GUI_GRAPHS_NODE_H
#define GUI_GRAPHS_NODE_H

#include <time.h>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

#include "colors.h"
#include "defines.h"
#include "services/font.h"


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

    void changeSelect();

    void fillColor(uint8_t colorID);

    sf::CircleShape circle{ NODE_RADIUS, 100 };
    sf::Text text{ FontStore::getFont() };
    char key;
    bool selected{ false };
    time_t selectTime;
};

#endif

