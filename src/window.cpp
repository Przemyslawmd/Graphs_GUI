
#include "window.h"

#include <string>

#include <SFML/System/Vector2.hpp>

#include "menu.h"
#include "services/font.h"


Window::Window()
{
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode({ 1600, 900 }, sf::Style::Titlebar ), "", sf::State::Windowed, settings);
    client = std::make_unique<Client>();
    model = std::make_unique<Model>();
    hold = std::make_unique<Hold>();
}


void Window::init()
{
    if (FontStore::createFont() == false) {
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
                handleMouseMove(event->getIf<sf::Event::MouseMoved>());
            }
            else if (event->is<sf::Event::Resized>()) {
                resize();
            }
            else if (event->is<sf::Event::TextEntered>()) {
                handleTextEntered(event->getIf<sf::Event::TextEntered>());
            }
        }
        window->clear(sf::Color::White);

        for (const auto& button : buttons) {
            window->draw(button);
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
        for (auto& [_, input] : inputs) {
            input.checkFocus();
            window->draw(input);
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
    setInputFocus(false, false);

    sf::Vector2i position = sf::Mouse::getPosition(*window);
    if (isOverAddNode(position)) {
        createNode();
        return;
    }
    if (isOverConnectNodes(position)) {
        createConnection();
        return;
    }
    if (isOverRemoveAll(position)) {
        removeGraph();
        return;
    }
    if (isOverRemoveNode(position)) {
        removeNode();
        return;
    }
    if (isOverNodeInput(position)) {
        setInputFocus(true, false);
        return;
    }
    if (isOverConnectInput(position)) {
        setInputFocus(false, true);
        return;
    }
    if (isOverBFS(position)) {
        traverseBFS();
        return;
    }
    if (isOverDFS(position)) {
        traverseDFS();
        return;
    }
    if (isOverShortestPath(position)) {
        shortestPath();
        return;
    }
    auto [index, shiftX, shiftY] = model->isMouseOverNode(position);
    if (index >= 0) {
        hold->activate(index, shiftX, shiftY);
    }
}


void Window::handleMouseRelease()
{
    if (hold->isMoved) {
        return;
    }

    auto& node = model->getNodes()[hold->index];
    node.changeSelect();
}


void Window::handleMouseMove(const sf::Event::MouseMoved* event)
{
    float x = event->position.x;
    float y = event->position.y;

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
    heldNode.setPosition({ x - radius - hold->shiftX, y - radius - hold->shiftY });

    for (size_t i = 0; i < heldNode.connections.size(); i++) {
        model->moveConnection(heldNode.connections[i]);
    }
    hold->isMoved = true;
}


void Window::handleTextEntered(const sf::Event::TextEntered* event)
{
    using enum Menu;
    if (inputs.at(NODE_INPUT).focus) {
        inputs.at(NODE_INPUT).updateText(static_cast<char>(event->unicode));
    }
    else if (inputs.at(CONNECTION_INPUT).focus) {
        inputs.at(CONNECTION_INPUT).updateText(static_cast<char>(event->unicode));
    }
}


void Window::createNode()
{
    const auto [result, key] = model->createNode(inputs.at(Menu::NODE_INPUT).text);
    if (result == Message::OK) {
        client->addNode(key.value());
        return;
    }
    setMessage(MessageStr.at(result));
}


void Window::removeNode()
{
    const auto [result, key] = model->removeNode();
    if (result == Message::OK) {
        client->removeNode(key.value());
        return;
    }
    setMessage(MessageStr.at(result));
}


void Window::removeGraph()
{
    model->removeAll();
    client->removeGraph();
}


void Window::createConnection()
{
    const auto [result, connInterface] = model->createConnection(inputs.at(Menu::CONNECTION_INPUT).text);
    if (result == Message::OK) {
        client->addEdge(connInterface.value().src, connInterface.value().dst, connInterface.value().weight);
        return;
    }
    setMessage(MessageStr.at(result));
}


void Window::traverseBFS()
{
    const auto [result, key] = model->getSelectedNode();
    if (result == Message::OK) {
        auto sequence = client->BFS(key.value());
        setMessage("BFS sequence: " + std::string(sequence->begin(), sequence->end()));
        return;
    }
    setMessage(MessageStr.at(result));
}


void Window::traverseDFS()
{
    const auto [result, key] = model->getSelectedNode();
    if (result == Message::OK) {
        auto sequence = client->DFS(key.value());
        setMessage("DFS sequence: " + std::string(sequence->begin(), sequence->end()));
        return;
    }
    setMessage(MessageStr.at(result));
}


void Window::shortestPath()
{
    const auto [result, src, dst] = model->getTwoSelectedNodes();
    if (result == Message::OK) {
        auto sequence = client->shortestPath(src.value(), dst.value());
        model->colorConnections(*sequence);
        return;
    }
    setMessage(MessageStr.at(result));
};


void Window::prepareMenu()
{
    auto& font = FontStore::getFont();
    for (const auto& [key, value] : buttonsData) {
        if (key == Menu::NODE_INPUT || key == Menu::CONNECTION_INPUT) {
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


void Window::prepareLines()
{
    sf::Vector2u size = { window->getSize().x, window->getSize().y };

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


void Window::setLinesPositions(const sf::Vector2u& size)
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
    using enum Line;
    lines.at(MESSAGE_UP).setSize({ size.x - 2 * MARGIN_X, 1 });
    lines.at(MESSAGE_BOTTOM).setSize({ size.x - 2 * MARGIN_X, 1 });

    lines.at(GRAPHS_UP).setSize({ size.x - 2 * MARGIN_X, 1 });
    lines.at(GRAPHS_BOTTOM).setSize({ size.x - 2 * MARGIN_X, 1 });
    lines.at(GRAPHS_LEFT).setSize({ 1, size.y - MARGIN_UP_GRAPHS - MARGIN_BOTTOM_GRAPHS });
    lines.at(GRAPHS_RIGHT).setSize({ 1, size.y - MARGIN_UP_GRAPHS - MARGIN_BOTTOM_GRAPHS });
}


void Window::setMessage(const std::string& text)
{
    auto& font = FontStore::getFont();
    message = std::make_unique<sf::Text>(font, text, 15);
    const auto& pos = lines.at(Line::MESSAGE_LEFT).getPosition();
    message->setPosition({ pos.x + 10, pos.y + 10 });
    message->setFillColor(sf::Color::Black);
}


void Window::setInputFocus(bool isFocusNodeInput, bool isFocusConnectionInput)
{
    inputs.at(Menu::NODE_INPUT).focus = isFocusNodeInput;
    inputs.at(Menu::CONNECTION_INPUT).focus = isFocusConnectionInput;
}

