
#ifndef GUI_GRAPHS_INPUT_H
#define GUI_GRAPHS_INPUT_H

#include <string>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>


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
    size_t verticalCounter;
};

#endif

