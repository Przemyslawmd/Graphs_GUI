
#ifndef GUI_GRAPHS_CONNECTION_H
#define GUI_GRAPHS_CONNECTION_H

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

#include "defines.h"
#include "services/font.h"

constexpr size_t ARROW_RADIUS = 10;


struct ConnectionData
{
    char src;
    char dst; 
    size_t weight;
};


enum class Level
{
    BASE,
    LOWER,
    UPPER
};


class Connection : public sf::Drawable
{
public:
    Connection(float length, char src, char dst, bool directed);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setCoordinates(const sf::Vector2f& srcPos, const sf::Vector2f& dstPos);
    void setSize(float length);

    void colorConnection();
    void resetColor();
    bool isColor() const;

    bool isMatch(char srcKey, char dstKey) const;

    void changeSelect();

    sf::RectangleShape line;
    sf::Text text{ FontStore::getFont() };
    char srcKey;
    char dstKey;
    bool selected{ false };
    bool directed;
    Level level{ Level::BASE };

private:
    sf::CircleShape arrow{ ARROW_RADIUS, 3 };
};

#endif

