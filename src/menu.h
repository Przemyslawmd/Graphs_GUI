
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
    const float posX;
    const float posTitle;
    const std::string title;
};


static const std::map<Indicator, Data> buttonsData = 
{
    { Indicator::ADD_NODE,      { 20.f,  45.f,  "Add Node" }},
    { Indicator::CONNECT_NODES, { 140.f, 150.f, "Connect Nodes" }},
    { Indicator::REMOVE_ALL,    { 260.f, 280.f, "Remove All" }}
};


static bool isOverMenu(const sf::Vector2i& pos, const Data& menu) 
{
    return pos.x > menu.posX && pos.x < menu.posX + MENU_WIDTH && pos.y > MENU_POS_Y && pos.y < MENU_POS_Y + MENU_HEIGHT;
}


static bool isOverAddNodeMenu(const sf::Vector2i& pos)
{
    const auto& menu = buttonsData.at(Indicator::ADD_NODE); 
    return isOverMenu(pos, menu);
}


static bool isOverConnectNodesMenu(const sf::Vector2i& pos)
{
    const auto& menu = buttonsData.at(Indicator::CONNECT_NODES); 
    return isOverMenu(pos, menu);
}


static bool isOverRemoveAllMenu(const sf::Vector2i& pos)
{
    const auto& menu = buttonsData.at(Indicator::REMOVE_ALL);
    return isOverMenu(pos, menu);
}

#endif

