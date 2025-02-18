
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


static const std::map<Action, Data> actionData = 
{
    { Action::NODE_INPUT,       { 20.f,  25.f,    INPUT_WIDTH,  std::nullopt }},
    { Action::NODE_ADD,         { 52.f,  82.f,    BUTTON_WIDTH, "Add Node" }},
    { Action::NODE_REMOVE,      { 174.f, 188.f,   BUTTON_WIDTH, "Remove Node" }},
    { Action::CONNECTION_INPUT, { 340.f, 345.f,   INPUT_WIDTH,  std::nullopt }},
    { Action::CONNECTION_ADD,   { 370.f, 380.f,   BUTTON_WIDTH, "Connect Nodes" }},
    { Action::REMOVE_ALL,       { 650.f, 675.f,   BUTTON_WIDTH, "Remove All" }},
    { Action::TRAVERSE_BFS,     { 840.f, 855.f,   BUTTON_WIDTH, "Traverse BFS" }},
    { Action::TRAVERSE_DFS,     { 960.f, 975.f,   BUTTON_WIDTH, "Traverse DFS" }},
    { Action::SHORTEST_PATH,    { 1100.f, 1115.f, BUTTON_WIDTH, "Shortest Path" }},
    { Action::RESET_PATH,       { 1220.f, 1245.f, BUTTON_WIDTH, "Reset Path" }},
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

