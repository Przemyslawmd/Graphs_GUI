
#ifndef GUI_GRAPHS_MENU_H
#define GUI_GRAPHS_MENU_H

#include <map>
#include <string>

#include "defines.h"


constexpr float MENU_HEIGHT = 22.f;
constexpr float MENU_WIDTH = 120.f;
constexpr float MENU_POS_Y = 5.f;


struct Data
{
    const float posX;
    const float posTitle;
    const std::string title;
};


static const std::map<Menu, Data> buttonsData = 
{
    { Menu::NODE_INPUT,    { 20.f,  25.f,    "" }},
    { Menu::ADD_NODE,      { 142.f, 172.f,  "Add Node" }},
    { Menu::CONNECT_NODES, { 262.f, 272.f,  "Connect Nodes" }},
    { Menu::REMOVE_ALL,    { 382.f, 407.f,  "Remove All" }},
    { Menu::TRAVERSE_BFS,  { 600.f, 613.f,  "Traverse BFS" }},
    { Menu::TRAVERSE_DFS,  { 720.f, 733.f,  "Traverse DFS" }},
};


static bool isOverMenu(const sf::Vector2i& pos, const Data& menu) 
{
    return pos.x > menu.posX && pos.x < menu.posX + MENU_WIDTH && pos.y > MENU_POS_Y && pos.y < MENU_POS_Y + MENU_HEIGHT;
}


static bool isOverNodeValueMenu(const sf::Vector2i& pos)
{
    const auto& menu = buttonsData.at(Menu::NODE_INPUT); 
    return isOverMenu(pos, menu);
}


static bool isOverAddNodeMenu(const sf::Vector2i& pos)
{
    const auto& menu = buttonsData.at(Menu::ADD_NODE); 
    return isOverMenu(pos, menu);
}


static bool isOverConnectNodesMenu(const sf::Vector2i& pos)
{
    const auto& menu = buttonsData.at(Menu::CONNECT_NODES); 
    return isOverMenu(pos, menu);
}


static bool isOverRemoveAllMenu(const sf::Vector2i& pos)
{
    const auto& menu = buttonsData.at(Menu::REMOVE_ALL);
    return isOverMenu(pos, menu);
}


static bool isOverBFSMenu(const sf::Vector2i& pos)
{
    const auto& menu = buttonsData.at(Menu::TRAVERSE_BFS);
    return isOverMenu(pos, menu);
}


static bool isOverDFSMenu(const sf::Vector2i& pos)
{
    const auto& menu = buttonsData.at(Menu::TRAVERSE_DFS);
    return isOverMenu(pos, menu);
}

#endif

