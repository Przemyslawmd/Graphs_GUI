
#include "window.h"

#include <ranges>
#include <thread>

#include <SFML/System/Vector2.hpp>

#include "services/directed.h"
#include "services/font.h"
#include "services/iofile.h"


Window::Window()
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


void Window::init()
{
    if (FontStore::createFont() == false) {
        return;
    }
    menu->prepareMenu();
    lines->prepareLines({ window->getSize().x, window->getSize().y });
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
        window->display();
    }
}


void Window::handleMousePress()
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
        hold->activate(index, shiftX, shiftY);
        return;
    }
    model->checkMouseOverConnection(position);
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


void Window::invokeAction(Action action)
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
        case SAVE_GRAPH:
            saveGraph();
            break;
        case READ_GRAPH:
            readGraph();
            break;
    }
}


void Window::createNode()
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


void Window::removeNodes()
{
    auto keys = model->removeNodes();
    if (keys == nullptr) {
        setMessage(MessageStr.at(Message::NODE_NOT_SELECTED));
        return;
    }
    client->removeNodes(std::move(keys));
}


void Window::removeGraph()
{
    model->removeAll();
    bool isDirected = Directed::isDirected();
    client->resetGraph(isDirected);
}


void Window::createConnection()
{
    const auto& text = menu->getInputText(Action::CONNECTION_INPUT);
    const auto [result, connData] = model->createConnection(text);
    if (result == Message::OK) {
        client->addEdge(connData.value().src, connData.value().dst, connData.value().weight);
        return;
    }
    setMessage(MessageStr.at(result));
}


void Window::removeConnection()
{
    auto edges = model->removeConnections();
    if (edges == nullptr) {
        setMessage(MessageStr.at(Message::CONNECTION_NOT_SELECTED));
        return;
    }
    client->removeEdges(std::move(edges));
}


void Window::callClientBFS(char key)
{
    auto sequence = client->BFS(key);
    setMessage("BFS sequence: " + std::string(sequence->begin(), sequence->end()));
}


void Window::traverseBFS()
{
    const auto key = model->getSelectedNode();
    if (key.has_value()) {
        std::thread th(&Window::callClientBFS, this, key.value());
        th.detach();
        return;
    }
    setMessage(MessageStr.at(Message::NODE_SELECT_ONE));
}


void Window::callClientDFS(char key)
{
    auto sequence = client->DFS(key);
    setMessage("DFS sequence: " + std::string(sequence->begin(), sequence->end()));
}


void Window::traverseDFS()
{
    const auto key = model->getSelectedNode();
    if (key.has_value()) {
        std::thread th(&Window::callClientDFS, this, key.value());
        th.detach();
        return;
    }
    setMessage(MessageStr.at(Message::NODE_SELECT_ONE));
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
    const auto [src, dst] = model->getTwoSelectedNodes();
    if (!src.has_value() || !dst.has_value()) {
        setMessage(MessageStr.at(Message::NODE_SELECT_TWO));
        return;
    }
    std::thread th(&Window::callClientShortestPath, this, src.value(), dst.value());
    th.detach();
};


void Window::callClientMinSpanningTree()
{
    auto edges = client->minSpanningTree();
    if (edges == nullptr) {
        setMessage(client->getLastErrorMessage());
        return;
    }
    model->colorEdges(*edges);
}


void Window::minSpanningTree()
{
    std::thread th(&Window::callClientMinSpanningTree, this);
    th.detach();
};


void Window::saveGraph()
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


void Window::readGraph()
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


void Window::resize()
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


void Window::setMessage(const std::string& text)
{
    auto& font = FontStore::getFont();
    message = std::make_unique<sf::Text>(font, text, 15);
    const auto& pos = lines->getMessageLine();
    message->setPosition({ pos.x + 10, pos.y + 10 });
    message->setFillColor(sf::Color::Black);
}

