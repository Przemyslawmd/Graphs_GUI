
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


static const std::map<Action, Data> buttonsData = 
{
    { Action::NODE_INPUT,       { 20.f,  25.f,    INPUT_WIDTH,  std::nullopt }},
    { Action::NODE_ADD,         { 52.f,  80.f,    BUTTON_WIDTH, "Add Node" }},
    { Action::NODE_REMOVE,      { 174.f, 188.f,   BUTTON_WIDTH, "Remove Node" }},
    { Action::CONNECTION_INPUT, { 340.f, 345.f,   INPUT_WIDTH,  std::nullopt }},
    { Action::CONNECTION_ADD,   { 370.f, 380.f,   BUTTON_WIDTH, "Connect Nodes" }},
    { Action::REMOVE_ALL,       { 650.f, 670.f,   BUTTON_WIDTH, "Remove All" }},
    { Action::TRAVERSE_BFS,     { 840.f, 853.f,   BUTTON_WIDTH, "Traverse BFS" }},
    { Action::TRAVERSE_DFS,     { 960.f, 973.f,   BUTTON_WIDTH, "Traverse DFS" }},
    { Action::SHORTEST_PATH,    { 1100.f, 1112.f, BUTTON_WIDTH, "Shortest Path" }},
    { Action::RESET_PATH,       { 1220.f, 1242.f, BUTTON_WIDTH, "Reset Path" }},
};


static bool isOverMenu(const sf::Vector2i& pos, const Data& menu) 
{
    return pos.x > menu.posX && pos.x < menu.posX + menu.width && pos.y > MENU_POS_Y && pos.y < MENU_POS_Y + MENU_HEIGHT;
}


static bool isOverNodeInput(const sf::Vector2i& pos)
{
    const auto& menu = buttonsData.at(Action::NODE_INPUT); 
    return isOverMenu(pos, menu);
}


static bool isOverAddNode(const sf::Vector2i& pos)
{
    const auto& menu = buttonsData.at(Action::NODE_ADD); 
    return isOverMenu(pos, menu);
}


static bool isOverRemoveNode(const sf::Vector2i& pos)
{
    const auto& menu = buttonsData.at(Action::NODE_REMOVE);
    return isOverMenu(pos, menu);
}


static bool isOverConnectNodes(const sf::Vector2i& pos)
{
    const auto& menu = buttonsData.at(Action::CONNECTION_ADD); 
    return isOverMenu(pos, menu);
}


static bool isOverConnectInput(const sf::Vector2i& pos)
{
    const auto& menu = buttonsData.at(Action::CONNECTION_INPUT); 
    return isOverMenu(pos, menu);
}


static bool isOverRemoveAll(const sf::Vector2i& pos)
{
    const auto& menu = buttonsData.at(Action::REMOVE_ALL);
    return isOverMenu(pos, menu);
}


static bool isOverBFS(const sf::Vector2i& pos)
{
    const auto& menu = buttonsData.at(Action::TRAVERSE_BFS);
    return isOverMenu(pos, menu);
}


static bool isOverDFS(const sf::Vector2i& pos)
{
    const auto& menu = buttonsData.at(Action::TRAVERSE_DFS);
    return isOverMenu(pos, menu);
}


static bool isOverShortestPath(const sf::Vector2i& pos)
{
    const auto& menu = buttonsData.at(Action::SHORTEST_PATH);
    return isOverMenu(pos, menu);
}


static bool isOverResetPath(const sf::Vector2i& pos)
{
    const auto& menu = buttonsData.at(Action::RESET_PATH);
    return isOverMenu(pos, menu);
}

#endif

