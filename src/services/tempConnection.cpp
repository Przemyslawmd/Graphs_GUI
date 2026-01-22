
#include "tempConnection.h"


TempConnection::TempConnection() : line{ sf::Vector2f{ 100.0f, LINE_WIDTH }} 
{
    line.setPosition({ 100, 100 });
    line.setFillColor({ colors.at(DEFAULT_COLOR).R, colors.at(DEFAULT_COLOR).G, colors.at(DEFAULT_COLOR).B });
    line.setOutlineColor(sf::Color::Black);
}


void TempConnection::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(line);
}

