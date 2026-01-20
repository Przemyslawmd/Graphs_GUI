
#ifndef GUI_GRAPHS_TEMP_H
#define GUI_GRAPHS_TEMP_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Font.hpp>

#include "config.h"


class TempLine : public sf::Drawable
{
public:
    

    int index;
    char key;
    float x;
    float y;

    sf::RectangleShape line;        

};

#endif