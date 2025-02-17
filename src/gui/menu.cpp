
#include "menu.h"

#include "services/font.h"


void Menu::prepareMenu()
{
    auto& font = FontStore::getFont();
    for (const auto& [key, value] : buttonsData) {
        if (key == Action::NODE_INPUT || key == Action::CONNECTION_INPUT) {
            inputs.emplace(key, Input{ value.width, MENU_HEIGHT, font });
            inputs.at(key).shape.setPosition({ value.posX, MENU_POS_Y });
            inputs.at(key).text.setPosition({ value.posTitle, MENU_POS_Y + 2.f });
            inputs.at(key).vertical.setPosition({ value.posTitle, MENU_POS_Y + 2.f });
        }
        else {
            auto& button = buttons.emplace_back( value.width, MENU_HEIGHT, font, value.title.value());
            button.shape.setPosition({ value.posX, MENU_POS_Y });
            button.text.setPosition({ value.posTitle, MENU_POS_Y + 2.f });
        }
    }
}


const std::vector<Button>& Menu::getButtons() const
{
    return buttons;
}


std::map<Action, Input>& Menu::getInputs()
{
    return inputs;
}


void Menu::setInputFocus(bool nodeInput, bool connectionInput)
{
    inputs.at(Action::NODE_INPUT).focus = nodeInput;
    inputs.at(Action::CONNECTION_INPUT).focus = connectionInput;
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
}

