
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
    const std::optional<std::string> title;
};


static const std::map<Menu, Data> buttonsData = 
{
    { Menu::NODE_INPUT,       { 20.f,  25.f,  INPUT_WIDTH,  std::nullopt }},
    { Menu::NODE_ADD,         { 52.f,  80.f,  BUTTON_WIDTH, "Add Node" }},
    { Menu::NODE_UPDATE,      { 174.f, 190.f, BUTTON_WIDTH, "Update Node" }},
    { Menu::CONNECTION_INPUT, { 340.f, 345.f, INPUT_WIDTH,  std::nullopt }},
    { Menu::CONNECTION_ADD,   { 370.f, 380.f, BUTTON_WIDTH, "Connect Nodes" }},
    { Menu::REMOVE_NODE,      { 530.f, 540.f, BUTTON_WIDTH, "Remove Node" }},
    { Menu::REMOVE_ALL,       { 650.f, 670.f, BUTTON_WIDTH, "Remove All" }},
    { Menu::TRAVERSE_BFS,     { 840.f, 853.f, BUTTON_WIDTH, "Traverse BFS" }},
    { Menu::TRAVERSE_DFS,     { 960.f, 973.f, BUTTON_WIDTH, "Traverse DFS" }},
};


static bool isOverMenu(const sf::Vector2i& pos, const Data& menu) 
{
    return pos.x > menu.posX && pos.x < menu.posX + menu.width && pos.y > MENU_POS_Y && pos.y < MENU_POS_Y + MENU_HEIGHT;
}


static bool isOverNodeInput(const sf::Vector2i& pos)
{
    const auto& menu = buttonsData.at(Menu::NODE_INPUT); 
    return isOverMenu(pos, menu);
}


static bool isOverAddNode(const sf::Vector2i& pos)
{
    const auto& menu = buttonsData.at(Menu::NODE_ADD); 
    return isOverMenu(pos, menu);
}


static bool isOverUpdateNode(const sf::Vector2i& pos)
{
    const auto& menu = buttonsData.at(Menu::NODE_UPDATE); 
    return isOverMenu(pos, menu);
}


static bool isOverConnectNodes(const sf::Vector2i& pos)
{
    const auto& menu = buttonsData.at(Menu::CONNECTION_ADD); 
    return isOverMenu(pos, menu);
}


static bool isOverConnectInput(const sf::Vector2i& pos)
{
    const auto& menu = buttonsData.at(Menu::CONNECTION_INPUT); 
    return isOverMenu(pos, menu);
}


static bool isOverRemoveNode(const sf::Vector2i& pos)
{
    const auto& menu = buttonsData.at(Menu::REMOVE_NODE);
    return isOverMenu(pos, menu);
}


static bool isOverRemoveAll(const sf::Vector2i& pos)
{
    const auto& menu = buttonsData.at(Menu::REMOVE_ALL);
    return isOverMenu(pos, menu);
}


static bool isOverBFS(const sf::Vector2i& pos)
{
    const auto& menu = buttonsData.at(Menu::TRAVERSE_BFS);
    return isOverMenu(pos, menu);
}


static bool isOverDFS(const sf::Vector2i& pos)
{
    const auto& menu = buttonsData.at(Menu::TRAVERSE_DFS);
    return isOverMenu(pos, menu);
}

#endif

