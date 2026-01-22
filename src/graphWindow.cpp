
#include "graphWindow.h"

#include <ranges>
#include <thread>

#include <SFML/System/Vector2.hpp>

#include "services/directed.h"
#include "services/font.h"
#include "services/iofile.h"


GraphWindow::GraphWindow()
{
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode({ 1600, 900 }, sf::Style::Titlebar ), "", sf::State::Windowed, settings);
    client = std::make_unique<Client>();
    model = std::make_unique<Model>();
    hold = std::make_unique<Hold>();
    menu = std::make_unique<Menu>();
    lines = std::make_unique<Lines>();
}


void GraphWindow::init()
{
    if (FontStore::createFont() == false) {
        return;
    }
    menu->prepareMenu();
    lines->prepareLines({ window->getSize().x, window->getSize().y });
    window->setVerticalSyncEnabled(true);
}


void GraphWindow::run()
{
    using namespace sf;

    while(window->isOpen()) {
        while(const std::optional event = window->pollEvent()) {
            if (event->is<Event::Closed>()) {
                window->close();
            }
            else if (event->is<Event::MouseButtonPressed>() && Mouse::isButtonPressed(Mouse::Button::Left)) {
                handleMousePressLeft();
            }
            else if (event->is<Event::MouseButtonPressed>() && Mouse::isButtonPressed(Mouse::Button::Right)) {
                handleMousePressRight();
            }
            else if (event->is<Event::MouseButtonReleased>() && hold->isLeftPress()) {
                handleMouseReleaseLeft();
                hold->reset();
            }
            else if (event->is<Event::MouseButtonReleased>() && hold->isRightPress()) {
                handleMouseReleaseRight();
                hold->reset();
            }
            else if (event->is<Event::MouseMoved>() && hold->isLeftPress()) {
                handleMouseMoveLeft(event->getIf<Event::MouseMoved>());
            }
            else if (event->is<Event::MouseMoved>() && hold->isRightPress()) {
                handleMouseMoveRight(event->getIf<Event::MouseMoved>());
            }
            else if (event->is<Event::Resized>()) {
                resize();
            }
            else if (event->is<Event::TextEntered>()) {
                const auto* textEvent = event->getIf<Event::TextEntered>();
                menu->checkTextEvent(static_cast<char>(textEvent->unicode));
            }
        }
        window->clear(Color::White);

        for (const auto& connection : model->getConnections()) {
            window->draw(connection);
        }
        for (const auto& node : model->getNodes()) {
            window->draw(node);
        }
        for (const auto& button : menu->getButtons()) {
            window->draw(button);
        } 
        for (const auto& line : lines->getLines() | std::views::values) {
            window->draw(line);
        }
        for (auto& input : menu->getInputs() | std::views::values) {
            input.checkFocus();
            window->draw(input);
        }
        for (auto& radio : menu->getRadio() | std::views::values) {
            window->draw(radio);
        }
        if (message) {
            window->draw(*message);
        }
        if (tempConnection) {
            window->draw(*tempConnection);
        }
        window->display();
    }
}


void GraphWindow::handleMousePressLeft()
{
    message.release();
    menu->setInputFocus(Action::NO_ACTION);

    sf::Vector2i position = sf::Mouse::getPosition(*window);
    Action action = menu->isOverActionMenu(position);
    if (action != Action::NO_ACTION) {
        invokeAction(action);
        return;
    }
    auto [index, shiftX, shiftY] = model->isMouseOverNode(position);
    if (index >= 0) {
        hold->activateLeft(index, shiftX, shiftY);
        return;
    }
    model->isMouseOverConnection(position);
}


void GraphWindow::handleMousePressRight()
{
    message.release();
    menu->setInputFocus(Action::NO_ACTION);

    sf::Vector2i position = sf::Mouse::getPosition(*window);
    auto [index, shiftX, shiftY] = model->isMouseOverNode(position);
    if (index >= 0) {
        hold->activateRight(index, shiftX, shiftY);
        tempConnection = std::make_unique<TempConnection>(position.x, position.y, index);
        return;
    }
}


void GraphWindow::handleMouseReleaseLeft()
{
    if (hold->isMoved) {
        return;
    }
    auto& node = model->getNodes()[hold->index.value()];
    node.changeSelect();
}

#include <iostream>

void GraphWindow::handleMouseReleaseRight()
{
    size_t srcNode = tempConnection->getSrcNodeIndex();
    tempConnection.reset();

    sf::Vector2i position = sf::Mouse::getPosition(*window);
    auto [dstNode, shiftX, shiftY] = model->isMouseOverNode(position);
    if (dstNode < 0 || srcNode == dstNode) {
        return;
    }

    const auto& text = menu->getInputText(Action::CONNECTION_INPUT);
    const auto [result, connData] = model->createConnection(srcNode, dstNode, text);
    if (result == Message::OK) {
        client->addEdge(connData.value().src, connData.value().dst, connData.value().weight);
        return;
    }
    setMessage(MessageStr.at(result));
}


void GraphWindow::handleMouseMoveLeft(const sf::Event::MouseMoved* event)
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

    auto& heldNode = model->getNodes()[hold->index.value()];
    float radius = heldNode.circle.getRadius();
    heldNode.setPosition({ x - radius - hold->shiftX, y - radius - hold->shiftY });
    model->moveNodeConnections(heldNode.key);
    hold->isMoved = true;
}


void GraphWindow::handleMouseMoveRight(const sf::Event::MouseMoved* event)
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

    tempConnection->adjustLine(x, y);
}


void GraphWindow::invokeAction(Action action)
{
    using enum Action;
    switch(action)
    {
        case NODE_ADD:
            createNode();
            break;
        case CONNECTION_ADD:
            createConnection();
            break;
        case NODE_REMOVE:
            removeNodes();
            break;
        case CONNECTION_REMOVE:
            removeConnection();
            break;
        case REMOVE_ALL:
            removeGraph();
            break;
        case TRAVERSE_BFS:
            traverseBFS();
            break;
        case TRAVERSE_DFS:
            traverseDFS();
            break;
        case SHORTEST_PATH:
            shortestPath();
            break;
        case RESET_PATH:
            model->resetPath();
            break;
        case MIN_SPANNING_TREE:
            minSpanningTree();
            break;
        case RESET_TREE:
            model->resetPath();
            break;
        case COLOR:
            colorGraph();
            break;
        case RESET_COLOR:
            resetColors();
            break;
        case SAVE_GRAPH:
            saveGraph();
            break;
        case READ_GRAPH:
            readGraph();
            break;
    }
}


void GraphWindow::createNode()
{
    const auto& text = menu->getInputText(Action::NODE_INPUT);
    const auto [result, key] = model->createNode(text);
    if (result == Message::OK) {
        client->addNode(key.value());
        return;
    }
    if (result == Message::RESET_GRAPH) {
        bool isDirected = Directed::isDirected();
        client->resetGraph(isDirected);
        client->addNode(key.value());
        return;
    }
    setMessage(MessageStr.at(result));
}


void GraphWindow::removeNodes()
{
    auto keys = model->removeNodes();
    if (keys == nullptr) {
        setMessage(MessageStr.at(Message::NODE_NOT_SELECTED));
        return;
    }
    client->removeNodes(*keys);
}


void GraphWindow::removeGraph()
{
    model->removeAll();
    bool isDirected = Directed::isDirected();
    client->resetGraph(isDirected);
}


void GraphWindow::createConnection()
{
    const auto& text = menu->getInputText(Action::CONNECTION_INPUT);
    const auto [result, connData] = model->createConnection(text);
    if (result == Message::OK) {
        client->addEdge(connData.value().src, connData.value().dst, connData.value().weight);
        return;
    }
    setMessage(MessageStr.at(result));
}


void GraphWindow::removeConnection()
{
    auto edges = model->removeConnections();
    if (edges == nullptr) {
        setMessage(MessageStr.at(Message::CONNECTION_NOT_SELECTED));
        return;
    }
    client->removeEdges(*edges);
}


void GraphWindow::traverseBFS()
{
    const auto key = model->getSelectedNodeKey();
    if (key.has_value()) {
        std::thread th(&GraphWindow::callBFS, this, key.value());
        th.detach();
        return;
    }
    setMessage(MessageStr.at(Message::NODE_SELECT_ONE));
}


void GraphWindow::callBFS(char key)
{
    auto sequence = client->BFS(key);
    setMessage("BFS sequence: " + std::string(sequence->begin(), sequence->end()));
}


void GraphWindow::traverseDFS()
{
    const auto key = model->getSelectedNodeKey();
    if (key.has_value()) {
        std::thread th(&GraphWindow::callDFS, this, key.value());
        th.detach();
        return;
    }
    setMessage(MessageStr.at(Message::NODE_SELECT_ONE));
}


void GraphWindow::callDFS(char key)
{
    auto sequence = client->DFS(key);
    setMessage("DFS sequence: " + std::string(sequence->begin(), sequence->end()));
}


void GraphWindow::shortestPath()
{
    const auto [src, dst] = model->getTwoSelectedNodesKeys();
    if (!src.has_value() || !dst.has_value()) {
        setMessage(MessageStr.at(Message::NODE_SELECT_TWO));
        return;
    }
    std::thread th(&GraphWindow::callShortestPath, this, src.value(), dst.value());
    th.detach();
};


void GraphWindow::callShortestPath(char src, char dst)
{
    auto sequence = client->shortestPath(src, dst);
    if (sequence == nullptr) {
        setMessage(client->getLastErrorMessage());
        return;
    }
    model->colorPath(*sequence);
}


void GraphWindow::minSpanningTree()
{
    std::thread th(&GraphWindow::callMinSpanningTree, this);
    th.detach();
};


void GraphWindow::callMinSpanningTree()
{
    auto edges = client->minSpanningTree();
    if (edges == nullptr) {
        setMessage(client->getLastErrorMessage());
        return;
    }
    model->colorEdges(*edges);
}


void GraphWindow::colorGraph()
{
    std::thread th(&GraphWindow::callColorGraph, this);
    th.detach();
};


void GraphWindow::callColorGraph()
{
    auto colors = client->colorNodes();
    if (colors == nullptr) {
        setMessage(client->getLastErrorMessage());
        return;
    }
    model->colorNodes(std::move(colors));
}


void GraphWindow::resetColors()
{
    std::thread th(&GraphWindow::callResetColorGraph, this);
    th.detach();
}


void GraphWindow::callResetColorGraph()
{
    client->resetColorNodes();
    model->resetColorNodes();
}


void GraphWindow::saveGraph()
{
    const auto& text = menu->getInputText(Action::FILE_INPUT);
    if (text.getString().isEmpty()) {
        setMessage(MessageStr.at(Message::NO_FILE_NAME));
        return;
    }
    IOFile iofile;
    if (!iofile.saveGraph(model->getNodes(), model->getConnections(), model->isDirected(), text.getString())) {
        setMessage(MessageStr.at(Message::WRITE_FILE_ERROR));
    }
}


void GraphWindow::readGraph()
{
    const auto& text = menu->getInputText(Action::FILE_INPUT);
    if (text.getString().isEmpty()) {
        setMessage(MessageStr.at(Message::NO_FILE_NAME));
        return;
    }

    IOFile iofile;
    if (!iofile.readGraph(text.getString())) {
        setMessage(MessageStr.at(Message::READ_FILE_ERROR));
        return;
    }

    bool directed = iofile.isDirected();
    model->removeAll();
    model->setDirected(directed);
    menu->setRadioSelect(directed);
    Directed::setDirected(directed);
    client->resetGraph(directed);

    const auto& nodesData = iofile.getNodesData();
    for (const auto& data : nodesData) {
        model->createNodeFromFile(data.key, data.posX, data.posY);
        client->addNode(data.key);
    }
    const auto& connectionData = iofile.getConnectionsData();
    for (const auto& conn : connectionData) {
        model->createConnectionFromFile(conn.src, conn.dst, conn.weight);
        client->addEdge(conn.src, conn.dst, conn.weight);
    }
}


void GraphWindow::resize()
{
    sf::Vector2u size = { window->getSize().x, window->getSize().y };
    sf::FloatRect newView({ 0, 0 }, { (float) size.x, (float) size.y });
    window->setView(sf::View(newView));
    lines->resizeLines(size);
    lines->setLinesPositions(size);

    if (message) {
        const auto pos = lines->getMessageLine();
        message->setPosition({ pos.x + 10, pos.y + 10 });
    }
}


void GraphWindow::setMessage(const std::string& text)
{
    auto& font = FontStore::getFont();
    message = std::make_unique<sf::Text>(font, text, 15);
    const auto& pos = lines->getMessageLine();
    message->setPosition({ pos.x + 10, pos.y + 10 });
    message->setFillColor(sf::Color::Black);
}

