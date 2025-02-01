
#ifndef GUI_GRAPHS_INPUT_H
#define GUI_GRAPHS_INPUT_H

#include <string>

#include <SFML/Graphics.hpp>


class Input : public sf::Drawable
{
public:
    Input(float width, float height, sf::Font& font);

    void checkFocus();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void updateText(const char letter); 

    sf::RectangleShape shape;
    sf::Text text;
    sf::Text vertical;

    bool focus;
    bool isVerticalToDraw;
    size_t verticalCounter;
};

#endif

