
#include "tempConnection.h"

#include "utils.h"


TempConnection::TempConnection(float srcX, float srcY, size_t srcNode) :
    line{ sf::Vector2f{ 0.0f, LINE_WIDTH }}, srcPos{ srcX, srcY }, srcNodeIndex{ srcNode }
{
    line.setPosition(srcPos);
    line.setFillColor({ colors.at(DEFAULT_COL).R, colors.at(DEFAULT_COL).G, colors.at(DEFAULT_COL).B });
    line.setOutlineColor(sf::Color::Black);
}


void TempConnection::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(line);
}


void TempConnection::adjustLine(float dstX, float dstY)
{
    float angle = calculateAngle( srcPos, { dstX, dstY });
    line.setRotation(sf::degrees(angle));
    float length = calculateConnectionLength( srcPos, { dstX, dstY });
    line.setSize({ length, LINE_WIDTH });
}

