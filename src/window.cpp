
#include <string>

#include <SFML/System/Vector2.hpp>

#include "config.h"
#include "defines.h"
#include "menu.h"
#include "window.h"


Window::Window()
{
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode({ 1600, 900 }, sf::Style::Titlebar ), "", sf::State::Windowed, settings);
    model = std::make_unique<Model>();
    hold = std::make_unique<Hold>();
}


void Window::init()
{
    if (!font.openFromFile(std::string(RESOURCES) + "Arial.ttf")) {
        return;
    }
    prepareMenu();
    prepareLines();
    window->setVerticalSyncEnabled(true);
}


void Window::run()
{
    while(window->isOpen()) {
        while(const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window->close();
            }
            else if (event->is<sf::Event::MouseButtonPressed>()) {
                handleMousePress();
            }
            else if (event->is<sf::Event::MouseButtonReleased>() && hold->isHeld) {
                handleMouseRelease();
                hold->reset();
            }
            else if (event->is<sf::Event::MouseMoved>() && hold->isHeld) {
                handleMouseMove(event);
            }
            else if (event->is<sf::Event::Resized>()) {
                resize();
            }
        }
        window->clear(sf::Color::White);

        for (const auto& button : buttons) {
            window->draw(button);
        }
        for (auto& input : inputs) {
            input.checkInput();
            //window->draw(input);
        }
        for (const auto& input : inputs) {
            //input.checkInput()
            window->draw(input);
        }
        for (const auto& connection : model->getConnections()) {
            window->draw(connection);
        }
        for (const auto& node : model->getNodes()) {
            window->draw(node);
        }
        for (const auto& [_, line] : lines) {
            window->draw(line);
        }
        if (message) {
            window->draw(*message);
        }
        window->display();
    }
}


void Window::handleMousePress()
{
    message.release();
    sf::Vector2i position = sf::Mouse::getPosition(*window);
    if (isOverAddNodeMenu(position)) {
        model->createNode(20);
        return;
    }
    if (isOverConnectNodesMenu(position)) {
        auto result = model->createConnection();
        if (result != Message::OK) {
            setMessage(MessageStr.at(result));
        }
        return;
    }
    if (isOverRemoveAllMenu(position)) {
        model->removeAll();
        return;
    }
    auto [index, shiftX, shiftY] = isMouseOverNode(position);
    if (index >= 0) {
        hold->activate(index, shiftX, shiftY);
    }
}


void Window::handleMouseRelease()
{
    if (hold->isMoved) {
        return;
    }

    auto& nodes = model->getNodes(); 
    auto& node = nodes[hold->index];
    auto& shape = node.circle;
    if (node.isIndicated == false) {
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(3.0f);
    }
    else if (node.isIndicated == true) {
        shape.setOutlineThickness(0);
    }
    node.isIndicated = !node.isIndicated; 
}


void Window::handleMouseMove(const std::optional<sf::Event> event)
{
    auto mouseEvent = event.value().getIf<sf::Event::MouseMoved>();
    float x = mouseEvent->position.x;
    float y = mouseEvent->position.y;

    sf::Vector2u size = { window->getSize().x, window->getSize().y };
    if (x > size.x - MARGIN_X - 20 || 
        x < MARGIN_X + 20 || 
        y > size.y - MARGIN_BOTTOM_GRAPHS - 20 ||
        y < MARGIN_UP_GRAPHS + 20) {
        return;
    }

    auto& nodes = model->getNodes();
    auto& heldNode = nodes[hold->index];

    float radius = heldNode.circle.getRadius();
    heldNode.circle.setPosition({ x - radius - hold->shiftX, y - radius - hold->shiftY });

    for (size_t i = 0; i < heldNode.connections.size(); i++) {
        model->moveConnection(heldNode.connections[i]);
    }
    hold->isMoved = true;
}


void Window::prepareMenu()
{
    for (const auto& [key, value] : buttonsData) {
        if (key != Indicator::NODE_NAME) {
            auto& button = buttons.emplace_back( MENU_WIDTH, MENU_HEIGHT, font, value.title);
            button.shape.setPosition({ value.posX, MENU_POS_Y });
            button.shape.setOutlineThickness(2);
            button.shape.setOutlineColor(sf::Color::Black);
            button.shape.setFillColor({ 223, 243, 246 });
            button.text.setFillColor(sf::Color::Black);
            button.text.setPosition({ value.posTitle, MENU_POS_Y + 2.f });
        } 
        else {
            auto& input = inputs.emplace_back( MENU_WIDTH, MENU_HEIGHT, font);
            input.shape.setPosition({ value.posX, MENU_POS_Y });
            input.shape.setFillColor(sf::Color::White);
            input.shape.setOutlineThickness(1);
            input.shape.setOutlineColor(sf::Color::Black);
            input.text.setFillColor(sf::Color::Black);
            input.text.setPosition({ value.posTitle, MENU_POS_Y + 2.f });
        }
    }
}


void Window::prepareLines()
{
    sf::Vector2u size = { window->getSize().x, window->getSize().y };

    lines.emplace(Line::MESSAGE_UP, sf::Vector2f{ size.x - 2 * MARGIN_X, 1 });
    lines.emplace(Line::MESSAGE_BOTTOM, sf::Vector2f{ size.x - 2 * MARGIN_X, 1 });
    lines.emplace(Line::MESSAGE_LEFT, sf::Vector2f{ 1, MESSAGE_AREA_HEIGHT });
    lines.emplace(Line::MESSAGE_RIGHT, sf::Vector2f{ 1, MESSAGE_AREA_HEIGHT });

    lines.emplace(Line::GRAPHS_UP, sf::Vector2f{ size.x - 2 * MARGIN_X, 1 });
    lines.emplace(Line::GRAPHS_BOTTOM, sf::Vector2f{ size.x - 2 * MARGIN_X, 1 });
    lines.emplace(Line::GRAPHS_LEFT, sf::Vector2f{ 1, size.y - MARGIN_BOTTOM_GRAPHS - MARGIN_UP_GRAPHS });
    lines.emplace(Line::GRAPHS_RIGHT, sf::Vector2f{ 1, size.y - MARGIN_BOTTOM_GRAPHS - MARGIN_UP_GRAPHS });

    setLinesPositions(size);

    for (auto& [_, line] : lines) {
        line.setFillColor(sf::Color::Black);
    }
}


void Window::setLinesPositions(const sf::Vector2u& size)
{
    lines.at(Line::MESSAGE_UP).setPosition( { MARGIN_X, size.y - MESSAGES_UP });
    lines.at(Line::MESSAGE_BOTTOM).setPosition( { MARGIN_X, size.y - MESSAGES_MARGIN_BOTTOM });
    lines.at(Line::MESSAGE_LEFT).setPosition( { MARGIN_X, size.y - MESSAGES_UP });
    lines.at(Line::MESSAGE_RIGHT).setPosition( { size.x - MARGIN_X, size.y - MESSAGES_UP });

    lines.at(Line::GRAPHS_UP).setPosition({ MARGIN_X, MARGIN_UP_GRAPHS });
    lines.at(Line::GRAPHS_BOTTOM).setPosition({ MARGIN_X, size.y - MARGIN_BOTTOM_GRAPHS });
    lines.at(Line::GRAPHS_LEFT).setPosition({ MARGIN_X, MARGIN_UP_GRAPHS });
    lines.at(Line::GRAPHS_RIGHT).setPosition({ size.x - MARGIN_X, MARGIN_UP_GRAPHS });
}


void Window::resize()
{
    sf::Vector2u size = { window->getSize().x, window->getSize().y };
    sf::FloatRect newView({ 0, 0 }, { (float) size.x, (float) size.y });
    window->setView(sf::View(newView));
    resizeLines(size);
    setLinesPositions(size);

    if (message) {
        const auto& pos = lines.at(Line::MESSAGE_LEFT).getPosition();
        message->setPosition({ pos.x + 10, pos.y + 10 });
    }
}


void Window::resizeLines(const sf::Vector2u& size)
{
    lines.at(Line::MESSAGE_UP).setSize({ size.x - 2 * MARGIN_X, 1 });
    lines.at(Line::MESSAGE_BOTTOM).setSize({ size.x - 2 * MARGIN_X, 1 });

    lines.at(Line::GRAPHS_UP).setSize({ size.x - 2 * MARGIN_X, 1 });
    lines.at(Line::GRAPHS_BOTTOM).setSize({ size.x - 2 * MARGIN_X, 1 });
    lines.at(Line::GRAPHS_LEFT).setSize({ 1, size.y - MARGIN_UP_GRAPHS - MARGIN_BOTTOM_GRAPHS });
    lines.at(Line::GRAPHS_RIGHT).setSize({ 1, size.y - MARGIN_UP_GRAPHS - MARGIN_BOTTOM_GRAPHS });
}


std::tuple<int, float, float> Window::isMouseOverNode(const sf::Vector2i& mousePos)
{
    auto& nodes = model->getNodes();
    for (size_t i = 0; i < nodes.size(); i++) {
        const auto& shape = nodes[i].circle;
        float radius = shape.getRadius();
        sf::Vector2f circlePos = shape.getPosition();
        float shiftX = mousePos.x - circlePos.x - radius;
        float shiftY = mousePos.y - circlePos.y - radius;
        int distance = sqrt(pow(shiftX, 2) + pow(shiftY, 2));
        if (distance <= radius) {
            return { i, shiftX, shiftY };
        }
    }
    return { -1, 0, 0 };
}


void Window::setMessage(const std::string& text)
{
    message = std::make_unique<sf::Text>(font, text, 15);
    const auto& pos = lines.at(Line::MESSAGE_LEFT).getPosition();
    message->setPosition({ pos.x + 10, pos.y + 10 });
    message->setFillColor(sf::Color::Black);
}

