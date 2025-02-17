
#ifndef GUI_GRAPHS_LINES_H
#define GUI_GRAPHS_LINES_H

#include <map>
#include <string>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include "defines.h"


class Lines
{
public:
    void prepareLines(const sf::Vector2u& size);
    void setLinesPositions(const sf::Vector2u& size);
    void resizeLines(const sf::Vector2u& size);

    std::map<Line, sf::RectangleShape>& getLines();
    sf::Vector2f getMessageLine();


private:
    std::map<Line, sf::RectangleShape> lines;
};

#endif

