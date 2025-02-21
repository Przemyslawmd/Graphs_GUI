
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
constexpr float MENU_POS_Y = 5.f;


struct Data
{
    const float posX;
    const float posTitle;
    const float width;
    const std::optional<std::string> title;
};


static const std::map<Action, Data> actionData = 
{
    { Action::NODE_INPUT,        { 20.f,   25.f,    30.f,  std::nullopt }},
    { Action::NODE_ADD,          { 52.f,   75.f,    110.f, "Add Node" }},
    { Action::NODE_REMOVE,       { 164.f,  174.f,   110.f, "Remove Node" }},
    { Action::CONNECTION_INPUT,  { 300.f,  305.f,   30.f,  std::nullopt }},
    { Action::CONNECTION_ADD,    { 330.f,  340.f,   120.f, "Connect Nodes" }},
    { Action::CONNECTION_REMOVE, { 450.f,  475.f,   120.f, "Disconnect" }},
    { Action::REMOVE_ALL,        { 600.f,  615.f,   100.f, "Remove All" }},
    { Action::TRAVERSE_BFS,      { 730.f,  742.f,   110.f, "Traverse BFS" }},
    { Action::TRAVERSE_DFS,      { 840.f,  850.f,   110.f, "Traverse DFS" }},
    { Action::SHORTEST_PATH,     { 980.f,  995.f,   110.f, "Shortest Path" }},
    { Action::RESET_PATH,        { 1090.f, 1110.f,  110.f, "Reset Path" }},
    { Action::SAVE_GRAPH,        { 1230.f, 1243.f,  100.f, "Save Graph" }},
    { Action::READ_GRAPH,        { 1330.f, 1343.f,  100.f, "Read Graph" }},
};


static bool isOverMenu(const sf::Vector2i& pos, const Data& menu) 
{
    return pos.x > menu.posX && pos.x < menu.posX + menu.width && pos.y > MENU_POS_Y && pos.y < MENU_POS_Y + MENU_HEIGHT;
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

