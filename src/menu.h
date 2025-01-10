
#ifndef STRUCTURES_GUI_MENU_H
#define STRUCTURES_GUI_MENU_H

#include <map>
#include <string>


struct MenuData
{
    float width;
    float height;
    float posX;
    float posY;
};


static const std::map<std::string, MenuData> Menu = 
{
    { "Add Node", { 80.f, 20.f, 0.f, 0.f }},
    { "Add Line", { 80.f, 20.f, 80.f, 0.f }}
};


static bool isAddNodeMenu(const sf::Vector2i& pos)
{
    const auto& menu = Menu.at("Add Node"); 
    return pos.x > menu.posX && pos.x < menu.posX + menu.width && pos.y > menu.posY && pos.y < menu.posY + menu.height;
}

#endif

