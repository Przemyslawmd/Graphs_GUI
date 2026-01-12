
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


constexpr float POS_Y_1 = 10.f;
constexpr float POS_Y_2 = 40.f;


enum class ActionType
{
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


using enum Action;
using enum ActionType;

static const std::map<Action, Data> actionData =
{
    { NODE_INPUT,        {   20.f,   25.f, POS_Y_1,  30.f, 22.f,  std::nullopt,       INPUT }},
    { NODE_ADD,          {   52.f,   75.f, POS_Y_1, 110.f, 22.f, "Add Node" ,         BUTTON }},
    { NODE_REMOVE,       {   52.f,   63.f, POS_Y_2, 110.f, 22.f, "Remove Node" ,      BUTTON }},

    { CONNECTION_INPUT,  {  180.f,  185.f, POS_Y_1,  30.f, 22.f,  std::nullopt,       INPUT }},
    { CONNECTION_ADD,    {  212.f,  222.f, POS_Y_1, 120.f, 22.f, "Connect Nodes",     BUTTON }},
    { CONNECTION_REMOVE, {  212.f,  235.f, POS_Y_2, 120.f, 22.f, "Disconnect",        BUTTON }},

    { TRAVERSE_BFS,      {  370.f,  381.f, POS_Y_1, 110.f, 22.f, "Traverse BFS",      BUTTON }},
    { TRAVERSE_DFS,      {  370.f,  381.f, POS_Y_2, 110.f, 22.f, "Traverse DFS",      BUTTON }},

    { SHORTEST_PATH,     {  500.f,  515.f, POS_Y_1, 110.f, 22.f, "Shortest Path",     BUTTON }},
    { RESET_PATH,        {  500.f,  522.f, POS_Y_2, 110.f, 22.f, "Reset Path",        BUTTON }},

    { MIN_SPANNING_TREE, {  630.f,  642.f, POS_Y_1, 140.f, 22.f, "Min Spanning Tree", BUTTON }},
    { RESET_TREE,        {  630.f,  665.f, POS_Y_2, 140.f, 22.f, "Reset Tree",        BUTTON }},

    { COLOR,             {  790.f,  825.f, POS_Y_1, 110.f, 22.f, "Color",             BUTTON }},
    { RESET_COLOR,       {  790.f,  810.f, POS_Y_2, 110.f, 22.f, "Reset Color",       BUTTON }},

    { REMOVE_ALL,        {  940.f,  955.f, POS_Y_1, 100.f, 22.f, "Remove All",        BUTTON }},

    { FILE_INPUT,        { 1060.f, 1065.f, POS_Y_1,  80.f, 22.f,  std::nullopt,       INPUT }},
    { SAVE_GRAPH,        { 1142.f, 1155.f, POS_Y_1, 100.f, 22.f, "Save Graph",        BUTTON }},
    { READ_GRAPH,        { 1142.f, 1155.f, POS_Y_2, 100.f, 22.f, "Read Graph",        BUTTON }},

    { RADIO_UNDIRECTED,  { 1310.f, 1335.f, POS_Y_1,  15.f, 15.f, "Undirected",        RADIO }},
    { RADIO_DIRECTED,    { 1310.f, 1335.f, POS_Y_2,  15.f, 15.f, "Directed",          RADIO }},
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

    void setRadioSelect(bool isDirected);

private:
    std::vector<Button> buttons;
    std::map<Action, Input> inputs;
    std::map<Action, Radio> radio;
};

#endif

