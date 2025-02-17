
#include "window.h"

#include <string>
#include <thread>

#include <SFML/System/Vector2.hpp>

#include "services/font.h"
#include "gui/menu.h"


Window::Window()
{
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode({ 1600, 900 }, sf::Style::Titlebar ), "", sf::State::Windowed, settings);
    client = std::make_unique<Client>();
    model = std::make_unique<Model>();
    hold = std::make_unique<Hold>();
    menu = std::make_unique<Menu>();
}


void Window::init()
{
    if (FontStore::createFont() == false) {
        return;
    }
    menu->prepareMenu();
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
                const auto* textEvent = event->getIf<sf::Event::TextEntered>();
                menu->checkTextEvent(static_cast<char>(textEvent->unicode));
            }
        }
        window->clear(sf::Color::White);

        for (const auto& button : menu->getButtons()) {
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
        for (auto& [_, input] : menu->getInputs()) {
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
    menu->setInputFocus(false, false);

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
        menu->setInputFocus(true, false);
        return;
    }
    if (isOverConnectInput(position)) {
        menu->setInputFocus(false, true);
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
    if (isOverResetPath(position)) {
        model->resetPath();
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

    auto& heldNode = model->getNodes()[hold->index];
    float radius = heldNode.circle.getRadius();
    heldNode.setPosition({ x - radius - hold->shiftX, y - radius - hold->shiftY });
    model->moveNodeConnections(heldNode.key);
    hold->isMoved = true;
}


void Window::createNode()
{
    const auto [result, key] = model->createNode(menu->getInputText(Action::NODE_INPUT));
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
    const auto [result, connInterface] = model->createConnection(menu->getInputText(Action::CONNECTION_INPUT));
    if (result == Message::OK) {
        client->addEdge(connInterface.value().src, connInterface.value().dst, connInterface.value().weight);
        return;
    }
    setMessage(MessageStr.at(result));
}


void Window::callClientBFS(char key)
{
    auto sequence = client->BFS(key);
    setMessage("BFS sequence: " + std::string(sequence->begin(), sequence->end()));
}


void Window::traverseBFS()
{
    const auto [result, key] = model->getSelectedNode();
    if (result == Message::OK) {
        std::thread th(&Window::callClientBFS, this, key.value());
        th.detach();
        return;
    }
    setMessage(MessageStr.at(result));
}


void Window::callClientDFS(char key)
{
    auto sequence = client->DFS(key);
    setMessage("DFS sequence: " + std::string(sequence->begin(), sequence->end()));
}


void Window::traverseDFS()
{
    const auto [result, key] = model->getSelectedNode();
    if (result == Message::OK) {
        std::thread th(&Window::callClientDFS, this, key.value());
        th.detach();
        return;
    }
    setMessage(MessageStr.at(result));
}


void Window::callClientShortestPath(char src, char dst)
{
    auto sequence = client->shortestPath(src, dst);
    if (sequence == nullptr) {
        setMessage(client->getLastErrorMessage());
        return;
    }
    model->colorPath(*sequence);
}


void Window::shortestPath()
{
    const auto [result, src, dst] = model->getTwoSelectedNodes();
    if (result != Message::OK) {
        setMessage(MessageStr.at(result));
        return;
    }
    std::thread th(&Window::callClientShortestPath, this, src.value(), dst.value());
    th.detach();
};


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

