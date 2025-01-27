
#ifndef GUI_GRAPHS_MENU_H
#define GUI_GRAPHS_MENU_H

#include <map>
#include <string>


constexpr float MENU_HEIGHT = 22.f;
constexpr float MENU_WIDTH = 120.f;
constexpr float MENU_POS_Y = 5.f;


enum class Indicator
{
    ADD_NODE,
    CONNECT_NODES,
    REMOVE_ALL
};


struct Data
{
    const float width;
    const float height;
    const float posX;
    const float posY;
    const float posTitle;
    const std::string title;
};


static const std::map<Indicator, Data> Menu = 
{
    { Indicator::ADD_NODE,      { MENU_WIDTH, MENU_HEIGHT, 20.f,  MENU_POS_Y, 45.f,  "Add Node" }},
    { Indicator::CONNECT_NODES, { MENU_WIDTH, MENU_HEIGHT, 140.f, MENU_POS_Y, 150.f, "Connect Nodes" }},
    { Indicator::REMOVE_ALL,    { MENU_WIDTH, MENU_HEIGHT, 260.f, MENU_POS_Y, 280.f, "Remove All" }}
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


static bool isOverRemoveAllMenu(const sf::Vector2i& pos)
{
    const auto& menu = Menu.at(Indicator::REMOVE_ALL);
    return isOverMenu(pos, menu);
}

#endif

