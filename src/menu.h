
#ifndef STRUCTURES_GUI_MENU_H
#define STRUCTURES_GUI_MENU_H

#include <map>
#include <string>


enum class Indicator
{
    ADD_NODE,
    CONNECT_NODES
};


struct Data
{
    const float width;
    const float height;
    const float posX;
    const float posY;
    const std::string title;
};


static const std::map<Indicator, Data> Menu = 
{
    { Indicator::ADD_NODE, { 80.f, 20.f, 0.f, 0.f, "Add Node" }},
    { Indicator::CONNECT_NODES, { 80.f, 20.f, 80.f, 0.f, "Connect Nodes" }}
};


static bool isAddNodeMenu(const sf::Vector2i& pos)
{
    const auto& menu = Menu.at(Indicator::ADD_NODE); 
    return pos.x > menu.posX && pos.x < menu.posX + menu.width && pos.y > menu.posY && pos.y < menu.posY + menu.height;
}

#endif

