
#ifndef GUI_GRAPHS_MENU_H
#define GUI_GRAPHS_MENU_H

#include <map>
#include <optional>
#include <string>
#include <vector>

#include <SFML/System/Vector2.hpp>

#include "defines.h"
#include "gui/button.h"
#include "gui/input.h"


constexpr float MENU_HEIGHT = 22.f;
constexpr float MENU_POS_Y_1 = 5.f;
constexpr float MENU_POS_Y_2 = 35.f;


struct Data
{
    const float posX;
    const float posTitle;
    const float posY;
    const float width;
    const std::optional<std::string> title;
};


static const std::map<Action, Data> actionData = 
{
    { Action::NODE_INPUT,        { 20.f,   25.f,   MENU_POS_Y_1, 30.f,  std::nullopt }},
    { Action::NODE_ADD,          { 52.f,   75.f,   MENU_POS_Y_1, 110.f, "Add Node" }},
    { Action::NODE_REMOVE,       { 52.f,   63.f,   MENU_POS_Y_2, 110.f, "Remove Node" }},
    { Action::CONNECTION_INPUT,  { 210.f,  215.f,  MENU_POS_Y_1, 30.f,  std::nullopt }},
    { Action::CONNECTION_ADD,    { 242.f,  252.f,  MENU_POS_Y_1, 120.f, "Connect Nodes" }},
    { Action::CONNECTION_REMOVE, { 242.f,  265.f,  MENU_POS_Y_2, 120.f, "Disconnect" }},
    { Action::TRAVERSE_BFS,      { 420.f,  431.f,  MENU_POS_Y_1, 110.f, "Traverse BFS" }},
    { Action::TRAVERSE_DFS,      { 420.f,  431.f,  MENU_POS_Y_2, 110.f, "Traverse DFS" }},
    { Action::SHORTEST_PATH,     { 590.f,  605.f,  MENU_POS_Y_1, 110.f, "Shortest Path" }},
    { Action::RESET_PATH,        { 590.f,  625.f,  MENU_POS_Y_2, 110.f, "Reset" }},
    { Action::MIN_SPANNING_TREE, { 760.f,  772.f,  MENU_POS_Y_1, 140.f, "Min Spanning Tree" }},
    { Action::RESET_TREE,        { 760.f,  810.f,  MENU_POS_Y_2, 140.f, "Reset" }},
    { Action::REMOVE_ALL,        { 940.f,  955.f,  MENU_POS_Y_1, 100.f, "Remove All" }},
    { Action::SAVE_GRAPH,        { 1080.f, 1093.f, MENU_POS_Y_1, 100.f, "Save Graph" }},
    { Action::READ_GRAPH,        { 1080.f, 1093.f, MENU_POS_Y_2, 100.f, "Read Graph" }},
};


static bool isOverMenu(const sf::Vector2i& pos, const Data& menu) 
{
    return pos.x > menu.posX && pos.x < menu.posX + menu.width && pos.y > menu.posY && pos.y < menu.posY + MENU_HEIGHT;
}


static Action isOverActionMenu(const sf::Vector2i& pos)
{
    using enum Action;
    if (isOverMenu(pos, actionData.at(NODE_INPUT))) {
        return NODE_INPUT;
    }
    if (isOverMenu(pos, actionData.at(NODE_ADD))) {
        return NODE_ADD;
    }
    if (isOverMenu(pos, actionData.at(NODE_REMOVE))) {
        return NODE_REMOVE;
    }
    if (isOverMenu(pos, actionData.at(CONNECTION_ADD))) {
        return CONNECTION_ADD;
    }
    if (isOverMenu(pos, actionData.at(CONNECTION_INPUT))) {
        return CONNECTION_INPUT;
    }
    if (isOverMenu(pos, actionData.at(CONNECTION_REMOVE))) {
        return CONNECTION_REMOVE;
    }
    if (isOverMenu(pos, actionData.at(REMOVE_ALL))) {
        return REMOVE_ALL;
    }
    if (isOverMenu(pos, actionData.at(TRAVERSE_BFS))) {
        return TRAVERSE_BFS;
    }
    if (isOverMenu(pos, actionData.at(TRAVERSE_DFS))) {
        return TRAVERSE_DFS;
    }
    if (isOverMenu(pos, actionData.at(SHORTEST_PATH))) {
        return SHORTEST_PATH;
    }
    if (isOverMenu(pos, actionData.at(RESET_PATH))) {
        return RESET_PATH;
    }
    if (isOverMenu(pos, actionData.at(MIN_SPANNING_TREE))) {
        return MIN_SPANNING_TREE;
    }
    if (isOverMenu(pos, actionData.at(RESET_TREE))) {
        return RESET_TREE;
    }
    if (isOverMenu(pos, actionData.at(SAVE_GRAPH))) {
        return SAVE_GRAPH;
    }
    if (isOverMenu(pos, actionData.at(READ_GRAPH))) {
        return READ_GRAPH;
    }
    return NO_ACTION;
}


class Menu
{
public:
    void prepareMenu();

    const std::vector<Button>& getButtons() const;
    std::map<Action, Input>& getInputs();

    void setInputFocus(bool nodeInput, bool connectionInput);

    sf::Text& getInputText(Action action);
    void checkTextEvent(char letter);

private:
    std::vector<Button> buttons;
    std::map<Action, Input> inputs;
};

#endif

