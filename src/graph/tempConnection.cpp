
#include "tempConnection.h"

#include "utils.h"


TempConnection::TempConnection(float x, float y) : line{ sf::Vector2f{ 0.0f, LINE_WIDTH }}, srcX{ x }, srcY{ y } 
{
    line.setPosition({ x, y });
    line.setFillColor({ colors.at(DEFAULT_COLOR).R, colors.at(DEFAULT_COLOR).G, colors.at(DEFAULT_COLOR).B });
    line.setOutlineColor(sf::Color::Black);
}


void TempConnection::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(line);
}


void TempConnection::adjustLine(float x, float y)
{
    float angle = calculateAngle({ srcX, srcY }, { x, y });
    line.setRotation(sf::degrees(angle));
    float length = calculateConnectionLength({ srcX, srcY }, { x, y });
    line.setSize({ length, LINE_WIDTH });
}

