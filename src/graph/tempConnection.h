
#ifndef GUI_GRAPHS_TEMP_H
#define GUI_GRAPHS_TEMP_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "../graph/colors.h"

constexpr size_t DEFAULT_COLOR = 0;
constexpr size_t LINE_WIDTH = 3;


class TempConnection : public sf::Drawable
{
public:
    TempConnection(float x, float y);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void adjustLine(float x, float y);

    int index;
    char key;
    float srcX;
    float srcY;

    sf::RectangleShape line;
};

#endif