
#ifndef GUI_GRAPHS_FONT_H
#define GUI_GRAPHS_FONT_H

#include <SFML/Graphics/Font.hpp>

#include "config.h"


class FontStore
{
public:
    static bool createFont()
    {
        return font.openFromFile(std::string(RESOURCES) + "Arial.ttf");
    }

    static sf::Font& getFont()
    {
        return font;
    }

private:
    inline static sf::Font font;
};


#endif

