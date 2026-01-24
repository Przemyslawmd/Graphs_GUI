
#include "menu.h"

#include "ranges"

#include "services/font.h"


void Menu::prepareMenu()
{
    using enum ActionType;
    auto& font = FontStore::getFont();
    for (const auto& [key, value] : actionData) {
        if (value.type == INPUT) {
            inputs.emplace(key, Input{ value.width, value.height, font });
            inputs.at(key).shape.setPosition({ value.posX, value.posY });
            inputs.at(key).text.setPosition({ value.posTitle, value.posY + 2.f });
            inputs.at(key).vertical.setPosition({ value.posTitle, value.posY + 2.f });
        }
        else if (value.type == BUTTON) {
            auto& button = buttons.emplace_back( value.width, value.height, font, value.title.value());
            button.shape.setPosition({ value.posX, value.posY });
            button.text.setPosition({ value.posTitle, value.posY + 2.f });
        }
        else {
            radio.emplace(key, Radio{ value.width, value.height, font, value.title.value() });
            radio.at(key).radio.setPosition({ value.posX, value.posY + 3 });
            radio.at(key).text.setPosition({ value.posTitle, value.posY + 2.f });
        }
    }
    radio.at(Action::RADIO_UNDIRECTED).setSelect(true);
}


const std::vector<Button>& Menu::getButtons() const
{
    return buttons;
}


std::map<Action, Input>& Menu::getInputs()
{
    return inputs;
}


std::map<Action, Radio>& Menu::getRadio()
{
    return radio;
}


Action Menu::isOverActionMenu(const sf::Vector2i& pos)
{
    using enum Action;
    if (isOverMenu(pos, actionData.at(NODE_INPUT))) {
        setInputFocus(NODE_INPUT);
        return NO_ACTION;
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
        setInputFocus(CONNECTION_INPUT);
        return NO_ACTION;
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
    if (isOverMenu(pos, actionData.at(COLOR))) {
        return COLOR;
    }
    if (isOverMenu(pos, actionData.at(RESET_COLOR))) {
        return RESET_COLOR;
    }
    if (isOverMenu(pos, actionData.at(FILE_INPUT))) {
        setInputFocus(FILE_INPUT);
        return NO_ACTION;
    }
    if (isOverMenu(pos, actionData.at(SAVE_GRAPH))) {
        return SAVE_GRAPH;
    }
    if (isOverMenu(pos, actionData.at(READ_GRAPH))) {
        return READ_GRAPH;
    }
    if (isOverMenu(pos, actionData.at(RADIO_UNDIRECTED))) {
        return radio.at(RADIO_UNDIRECTED).isSelected() ? NO_ACTION : SET_GRAPH_UNDIRECTED;
    }
    if (isOverMenu(pos, actionData.at(RADIO_DIRECTED))) {
        return radio.at(RADIO_DIRECTED).isSelected() ? NO_ACTION : SET_GRAPH_DIRECTED;
    }

    return NO_ACTION;
}


void Menu::setInputFocus(Action action)
{
    for (auto& key : inputs | std::views::keys) {
        inputs.at(key).focus = (key == action);
    }
}


sf::Text& Menu::getInputText(Action action)
{
    return inputs.at(action).text;
}


void Menu::checkTextEvent(char letter)
{
    using enum Action;
    if (inputs.at(NODE_INPUT).focus) {
        inputs.at(NODE_INPUT).updateText(letter);
    }
    else if (inputs.at(CONNECTION_INPUT).focus) {
        inputs.at(CONNECTION_INPUT).updateText(letter);
    }
    else if (inputs.at(FILE_INPUT).focus) {
        inputs.at(FILE_INPUT).updateText(letter);
    }
}


void Menu::setRadioGraphType(bool isDirected)
{
    radio.at(Action::RADIO_DIRECTED).setSelect(isDirected);
    radio.at(Action::RADIO_UNDIRECTED).setSelect(!isDirected);
}

