
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
    REMOVE_ALL,
    NODE_NAME
};


struct Data
{
    const float posX;
    const float posTitle;
    const std::string title;
};


static const std::map<Indicator, Data> buttonsData = 
{
    { Indicator::NODE_NAME,     { 20.f,  25.f,    "" }},
    { Indicator::ADD_NODE,      { 142.f, 172.f,  "Add Node" }},
    { Indicator::CONNECT_NODES, { 262.f, 272.f,  "Connect Nodes" }},
    { Indicator::REMOVE_ALL,    { 382.f, 407.f,  "Remove All" }},
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

