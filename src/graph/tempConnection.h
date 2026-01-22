
#ifndef GUI_GRAPHS_TEMP_H
#define GUI_GRAPHS_TEMP_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "../graph/colors.h"

constexpr size_t LINE_WIDTH = 3;


class TempConnection : public sf::Drawable
{
public:
    TempConnection(float srcX, float srcY, size_t srcNode);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void adjustLine(float x, float y);

    size_t getSrcNodeIndex() const 
    {
        return srcNodeIndex;
    }

private:
    sf::RectangleShape line;

    size_t srcNodeIndex;
    sf::Vector2f srcPos;
};

#endif