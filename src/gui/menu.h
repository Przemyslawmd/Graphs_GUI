
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
#include "gui/radio.h"


constexpr float POS_Y_1 = 5.f;
constexpr float POS_Y_2 = 35.f;


enum class ActionType {
    BUTTON,
    INPUT,
    RADIO
};


struct Data
{
    const float posX;
    const float posTitle;
    const float posY;
    const float width;
    const float height;
    const std::optional<std::string> title;
    const ActionType type;
};


static const std::map<Action, Data> actionData =
{
    { Action::NODE_INPUT,        {   20.f,   25.f, POS_Y_1,  30.f, 22.f,  std::nullopt,       ActionType::INPUT }},
    { Action::NODE_ADD,          {   52.f,   75.f, POS_Y_1, 110.f, 22.f, "Add Node" ,         ActionType::BUTTON }},
    { Action::NODE_REMOVE,       {   52.f,   63.f, POS_Y_2, 110.f, 22.f, "Remove Node" ,      ActionType::BUTTON }},
    { Action::CONNECTION_INPUT,  {  210.f,  215.f, POS_Y_1,  30.f, 22.f,  std::nullopt,       ActionType::INPUT }},
    { Action::CONNECTION_ADD,    {  242.f,  252.f, POS_Y_1, 120.f, 22.f, "Connect Nodes",     ActionType::BUTTON }},
    { Action::CONNECTION_REMOVE, {  242.f,  265.f, POS_Y_2, 120.f, 22.f, "Disconnect",        ActionType::BUTTON }},
    { Action::TRAVERSE_BFS,      {  420.f,  431.f, POS_Y_1, 110.f, 22.f, "Traverse BFS",      ActionType::BUTTON }},
    { Action::TRAVERSE_DFS,      {  420.f,  431.f, POS_Y_2, 110.f, 22.f, "Traverse DFS",      ActionType::BUTTON }},
    { Action::SHORTEST_PATH,     {  590.f,  605.f, POS_Y_1, 110.f, 22.f, "Shortest Path",     ActionType::BUTTON }},
    { Action::RESET_PATH,        {  590.f,  625.f, POS_Y_2, 110.f, 22.f, "Reset",             ActionType::BUTTON }},
    { Action::MIN_SPANNING_TREE, {  760.f,  772.f, POS_Y_1, 140.f, 22.f, "Min Spanning Tree", ActionType::BUTTON }},
    { Action::RESET_TREE,        {  760.f,  810.f, POS_Y_2, 140.f, 22.f, "Reset",             ActionType::BUTTON }},
    { Action::REMOVE_ALL,        {  940.f,  955.f, POS_Y_1, 100.f, 22.f, "Remove All",        ActionType::BUTTON }},
    { Action::FILE_INPUT,        { 1080.f, 1085.f, POS_Y_1,  80.f, 22.f,  std::nullopt,       ActionType::INPUT }},
    { Action::SAVE_GRAPH,        { 1162.f, 1175.f, POS_Y_1, 100.f, 22.f, "Save Graph",        ActionType::BUTTON }},
    { Action::READ_GRAPH,        { 1162.f, 1175.f, POS_Y_2, 100.f, 22.f, "Read Graph",        ActionType::BUTTON }},
    { Action::RADIO_UNDIRECTED,  { 1310.f, 1335.f, POS_Y_1,  15.f, 15.f, "Undirected",        ActionType::RADIO }},
    { Action::RADIO_DIRECTED,    { 1310.f, 1335.f, POS_Y_2,  15.f, 15.f, "Directed",          ActionType::RADIO }},
};


static bool isOverMenu(const sf::Vector2i& pos, const Data& menu) 
{
    return pos.x > menu.posX && pos.x < menu.posX + menu.width && pos.y > menu.posY && pos.y < menu.posY + menu.height;
}


class Menu
{
public:
    void prepareMenu();

    Action isOverActionMenu(const sf::Vector2i& pos);

    const std::vector<Button>& getButtons() const;
    std::map<Action, Input>& getInputs();
    std::map<Action, Radio>& getRadio();

    void setInputFocus(Action);

    sf::Text& getInputText(Action);
    void checkTextEvent(char letter);

private:
    std::vector<Button> buttons;
    std::map<Action, Input> inputs;
    std::map<Action, Radio> radio;
};

#endif

