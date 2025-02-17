
#include "lines.h"


void Lines::prepareLines(const sf::Vector2u& size)
{
    using enum Line;
    lines.emplace(MESSAGE_UP, sf::Vector2f{ size.x - 2 * MARGIN_X, 1 });
    lines.emplace(MESSAGE_BOTTOM, sf::Vector2f{ size.x - 2 * MARGIN_X, 1 });
    lines.emplace(MESSAGE_LEFT, sf::Vector2f{ 1, MESSAGE_AREA_HEIGHT });
    lines.emplace(MESSAGE_RIGHT, sf::Vector2f{ 1, MESSAGE_AREA_HEIGHT });

    lines.emplace(GRAPHS_UP, sf::Vector2f{ size.x - 2 * MARGIN_X, 1 });
    lines.emplace(GRAPHS_BOTTOM, sf::Vector2f{ size.x - 2 * MARGIN_X, 1 });
    lines.emplace(GRAPHS_LEFT, sf::Vector2f{ 1, size.y - MARGIN_BOTTOM_GRAPHS - MARGIN_UP_GRAPHS });
    lines.emplace(GRAPHS_RIGHT, sf::Vector2f{ 1, size.y - MARGIN_BOTTOM_GRAPHS - MARGIN_UP_GRAPHS });

    setLinesPositions(size);

    for (auto& [_, line] : lines) {
        line.setFillColor(sf::Color::Black);
    }
}


std::map<Line, sf::RectangleShape>& Lines::getLines()
{
    return lines;
}


void Lines::setLinesPositions(const sf::Vector2u& size)
{
    using enum Line;
    lines.at(MESSAGE_UP).setPosition({ MARGIN_X, size.y - MESSAGES_UP });
    lines.at(MESSAGE_BOTTOM).setPosition({ MARGIN_X, size.y - MESSAGES_MARGIN_BOTTOM });
    lines.at(MESSAGE_LEFT).setPosition({ MARGIN_X, size.y - MESSAGES_UP });
    lines.at(MESSAGE_RIGHT).setPosition({ size.x - MARGIN_X, size.y - MESSAGES_UP });

    lines.at(GRAPHS_UP).setPosition({ MARGIN_X, MARGIN_UP_GRAPHS });
    lines.at(GRAPHS_BOTTOM).setPosition({ MARGIN_X, size.y - MARGIN_BOTTOM_GRAPHS });
    lines.at(GRAPHS_LEFT).setPosition({ MARGIN_X, MARGIN_UP_GRAPHS });
    lines.at(GRAPHS_RIGHT).setPosition({ size.x - MARGIN_X, MARGIN_UP_GRAPHS });
}


void Lines::resizeLines(const sf::Vector2u& size)
{
    using enum Line;
    lines.at(MESSAGE_UP).setSize({ size.x - 2 * MARGIN_X, 1 });
    lines.at(MESSAGE_BOTTOM).setSize({ size.x - 2 * MARGIN_X, 1 });

    lines.at(GRAPHS_UP).setSize({ size.x - 2 * MARGIN_X, 1 });
    lines.at(GRAPHS_BOTTOM).setSize({ size.x - 2 * MARGIN_X, 1 });
    lines.at(GRAPHS_LEFT).setSize({ 1, size.y - MARGIN_UP_GRAPHS - MARGIN_BOTTOM_GRAPHS });
    lines.at(GRAPHS_RIGHT).setSize({ 1, size.y - MARGIN_UP_GRAPHS - MARGIN_BOTTOM_GRAPHS });
}


sf::Vector2f Lines::getMessageLine()
{
    return lines.at(Line::MESSAGE_LEFT).getPosition();
}

