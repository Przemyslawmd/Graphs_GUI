
#ifndef GUI_GRAPHS_MENU_H
#define GUI_GRAPHS_MENU_H

#include <map>
#include <string>

#include "defines.h"


constexpr float MENU_HEIGHT = 22.f;
constexpr float BUTTON_WIDTH = 120.f;
constexpr float INPUT_WIDTH = 30.f;
constexpr float MENU_POS_Y = 5.f;


struct Data
{
    const float posX;
    const float posTitle;
    const float width;
    const std::string title;
};


static const std::map<Menu, Data> buttonsData = 
{
    { Menu::NODE_INPUT,    { 20.f,  25.f,  INPUT_WIDTH,  "" }},
    { Menu::NODE_ADD,      { 52.f,  80.f,  BUTTON_WIDTH, "Add Node" }},
    { Menu::NODE_UPDATE,   { 174.f, 190.f, BUTTON_WIDTH, "Update Node" }},
    { Menu::CONNECT_NODES, { 340.f, 350.f, BUTTON_WIDTH, "Connect Nodes" }},
    { Menu::REMOVE_NODE,   { 500.f, 510.f, BUTTON_WIDTH, "Remove Node" }},
    { Menu::REMOVE_ALL,    { 620.f, 640.f, BUTTON_WIDTH, "Remove All" }},
    { Menu::TRAVERSE_BFS,  { 810.f, 823.f, BUTTON_WIDTH, "Traverse BFS" }},
    { Menu::TRAVERSE_DFS,  { 930.f, 943.f, BUTTON_WIDTH, "Traverse DFS" }},
};


static bool isOverMenu(const sf::Vector2i& pos, const Data& menu) 
{
    return pos.x > menu.posX && pos.x < menu.posX + menu.width && pos.y > MENU_POS_Y && pos.y < MENU_POS_Y + MENU_HEIGHT;
}


static bool isOverNodeValueMenu(const sf::Vector2i& pos)
{
    const auto& menu = buttonsData.at(Menu::NODE_INPUT); 
    return isOverMenu(pos, menu);
}


static bool isOverAddNodeMenu(const sf::Vector2i& pos)
{
    const auto& menu = buttonsData.at(Menu::NODE_ADD); 
    return isOverMenu(pos, menu);
}


static bool isOverUpdateNodeMenu(const sf::Vector2i& pos)
{
    const auto& menu = buttonsData.at(Menu::NODE_UPDATE); 
    return isOverMenu(pos, menu);
}


static bool isOverConnectNodesMenu(const sf::Vector2i& pos)
{
    const auto& menu = buttonsData.at(Menu::CONNECT_NODES); 
    return isOverMenu(pos, menu);
}


static bool isOverRemoveNodesMenu(const sf::Vector2i& pos)
{
    const auto& menu = buttonsData.at(Menu::REMOVE_NODE);
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

