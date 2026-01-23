
#ifndef GUI_GRAPHS_CONNECTION_H
#define GUI_GRAPHS_CONNECTION_H

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>


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
    sf::Text text;
    char srcKey;
    char dstKey;
    bool selected;
    bool directed;
    Level level;

private:
    sf::CircleShape arrow;
};

#endif

