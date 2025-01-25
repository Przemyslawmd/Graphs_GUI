
#ifndef GUI_GRAPHS_MENU_H
#define GUI_GRAPHS_MENU_H

#include <map>
#include <string>


constexpr float MENU_HEIGHT = 22.f;
constexpr float MENU_POS_Y = 5.f;


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
    { Indicator::ADD_NODE, { 80.f, MENU_HEIGHT, 5.f, MENU_POS_Y, "Add Node" }},
    { Indicator::CONNECT_NODES, { 120.f, MENU_HEIGHT, 85.f, MENU_POS_Y, "Connect Nodes" }}
};


static bool isOverMenu(const sf::Vector2i& pos, const Data& menu) 
{
    return pos.x > menu.posX && pos.x < menu.posX + menu.width && pos.y > menu.posY && pos.y < menu.posY + menu.height;
}


static bool isOverAddNodeMenu(const sf::Vector2i& pos)
{
    const auto& menu = Menu.at(Indicator::ADD_NODE); 
    return isOverMenu(pos, menu);
}


static bool isOverConnectNodesMenu(const sf::Vector2i& pos)
{
    const auto& menu = Menu.at(Indicator::CONNECT_NODES); 
    return isOverMenu(pos, menu);
}

#endif

