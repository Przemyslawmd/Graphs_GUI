
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


class Connection : public sf::Drawable
{
public:
    Connection(float length, char src, char dst);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setCoordinates(sf::Vector2f& srcPos, sf::Vector2f& dstPos);

    bool isMatch(char node_1, char node_2) const;
    bool isColor() const;
    void changeSelect();

    sf::RectangleShape line;
    sf::CircleShape arrow;
    sf::Text text;
    char srcKey;
    char dstKey;
    bool selected;
    bool directed;
};

#endif

