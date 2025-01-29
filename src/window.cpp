
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
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode({ DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT }, sf::Style::Titlebar ),
                                                "", sf::State::Windowed, settings);
    window->setVerticalSyncEnabled(true);
    model = std::make_unique<Model>();
}


void Window::init()
{
    if (!font.openFromFile(std::string(RESOURCES) + "Arial.ttf")) {
        return;
    }
    prepareMenu();
    prepareMessageArea();
    prepareGraphArea();
    hold.isHeld = false;
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
            else if (event->is<sf::Event::MouseButtonReleased>() && hold.isHeld) {
                handleMouseRelease();
                hold = { false, false, -1, 0, 0 };
            }
            else if (event->is<sf::Event::MouseMoved>() && hold.isHeld) {
                handleMouseMove(event);
            }
            else if (event->is<sf::Event::Resized>()) {
                resize();
            }
        }
        window->clear(sf::Color::White);

        for (const auto& button : buttons) {
            window->draw(button.shape);
            window->draw(button.text);
        }
        for (const auto& connection : model->getConnections()) {
            window->draw(connection.line);
        }
        for (const auto& node : model->getNodes()) {
            window->draw(node.circle);
        }
        for (const auto& boundary : graphArea) {
            window->draw(boundary);
        }
        window->draw(messageArea);
        window->draw(messages[0]);
        window->display();
    }
}


void Window::handleMousePress()
{
    messages[0].setString("");
    sf::Vector2i position = sf::Mouse::getPosition(*window);
    if (isOverAddNodeMenu(position)) {
        model->createNode(20);
        return;
    }
    if (isOverConnectNodesMenu(position)) {
        auto message = model->createConnection();
        if (message != Message::OK) {
            messages[0].setString(MessageStr.at(message));
        }
        return;
    }
    if (isOverRemoveAllMenu(position)) {
        model->removeAll();
        return;
    }
    auto [index, shiftX, shiftY] = isMouseOverNode(position);
    if (index >= 0) {
        hold = { true, false, index, shiftX, shiftY };
    }
}


void Window::handleMouseRelease()
{
    if (hold.isMoved) {
        return;
    }

    auto& nodes = model->getNodes(); 
    auto& shape = nodes[hold.index].circle;
    if (nodes[hold.index].isIndicated == false) {
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(3.0f);
        nodes[hold.index].isIndicated = true;
    }
    else if (nodes[hold.index].isIndicated == true) {
        shape.setOutlineThickness(0);
        nodes[hold.index].isIndicated = false;
    }
}


void Window::handleMouseMove(const std::optional<sf::Event> event)
{
    auto mouseEvent = event.value().getIf<sf::Event::MouseMoved>();
    float x = mouseEvent->position.x;
    float y = mouseEvent->position.y;

    sf::Vector2u size = { window->getSize().x, window->getSize().y };
    if (x > size.x - GRAPH_AREA_X_MARGIN - 20 || 
        x < GRAPH_AREA_X_MARGIN + 20 || 
        y > size.y - GRAPH_AREA_Y_MARGIN_BOTTOM - 20 ||
        y < GRAPH_AREA_Y_MARGIN_UP + 20) {
        return;
    }
     
    auto& nodes = model->getNodes();
    auto& heldNode = nodes[hold.index];

    float radius = heldNode.circle.getRadius();
    heldNode.circle.setPosition({ x - radius - hold.shiftX, y - radius - hold.shiftY });

    for (size_t i = 0; i < heldNode.connections.size(); i++) {
        model->moveConnection(heldNode.connections[i]);
    }
    hold.isMoved = true;
}


void Window::prepareMenu()
{
    for (const auto& [key, value] : buttonsData) {
        auto& menu = buttons.emplace_back( MENU_WIDTH, MENU_HEIGHT, font, value.title);
        menu.shape.setPosition({ value.posX, MENU_POS_Y });
        menu.shape.setFillColor(sf::Color::White);
        menu.shape.setOutlineThickness(1);
        menu.shape.setOutlineColor(sf::Color::Black);
        menu.text.setFillColor(sf::Color::Black);
        menu.text.setPosition({ value.posTitle, MENU_POS_Y + 2.f });
    }
}


void Window::prepareMessageArea()
{
    messageArea = sf::RectangleShape{ sf::Vector2f{ DEFAULT_WINDOW_WIDTH - 40.f, MESSAGE_AREA_HEIGHT }};
    messageArea.setPosition( sf::Vector2f{ MESSAGE_AREA_X, DEFAULT_WINDOW_HEIGHT - 60.f });
    messageArea.setOutlineThickness(1);
    messageArea.setOutlineColor(sf::Color::Black);

    messages.emplace_back( font, "", 15 );
    messages[0].setPosition(sf::Vector2f{ MESSAGE_X, 850.f });
    messages[0].setFillColor(sf::Color::Black);
}

void Window::prepareGraphArea()
{
    auto& up = graphArea.emplace_back( sf::Vector2f{ DEFAULT_WINDOW_WIDTH - 2 * GRAPH_AREA_X_MARGIN, 1 });
    up.setPosition({ GRAPH_AREA_X_MARGIN, GRAPH_AREA_Y_MARGIN_UP});
    up.setFillColor(sf::Color::Black);

    auto& bottom = graphArea.emplace_back( sf::Vector2f{ DEFAULT_WINDOW_WIDTH - 2 * GRAPH_AREA_X_MARGIN, 1 });
    bottom.setPosition({ GRAPH_AREA_X_MARGIN, DEFAULT_WINDOW_HEIGHT - GRAPH_AREA_Y_MARGIN_BOTTOM });
    bottom.setFillColor(sf::Color::Black);

    auto& left = graphArea.emplace_back( sf::Vector2f{ 1, DEFAULT_WINDOW_HEIGHT - GRAPH_AREA_Y_MARGIN_BOTTOM - GRAPH_AREA_Y_MARGIN_UP });
    left.setPosition({ GRAPH_AREA_X_MARGIN, GRAPH_AREA_Y_MARGIN_UP });
    left.setFillColor(sf::Color::Black);

    auto& right = graphArea.emplace_back( sf::Vector2f{ 1, DEFAULT_WINDOW_HEIGHT - GRAPH_AREA_Y_MARGIN_BOTTOM - GRAPH_AREA_Y_MARGIN_UP });
    right.setPosition({ DEFAULT_WINDOW_WIDTH - GRAPH_AREA_X_MARGIN, GRAPH_AREA_Y_MARGIN_UP });
    right.setFillColor(sf::Color::Black);
}


void Window::resize()
{
    sf::Vector2u size = { window->getSize().x, window->getSize().y };
    sf::FloatRect newView({ 0, 0 }, { (float) size.x, (float) size.y });
    window->setView(sf::View(newView));

    resizeMessageArea(size);
    resizeGraphArea(size);
}


void Window::resizeMessageArea(const sf::Vector2u& size)
{
    messageArea.setSize({ size.x - 40.f, MESSAGE_AREA_HEIGHT });
    messageArea.setPosition(sf::Vector2f{ MESSAGE_AREA_X, size.y - MESSAGE_AREA_BOTTOM_DISTANCE });
    messages[0].setPosition(sf::Vector2f{ MESSAGE_X, size.y - MESSAGE_BOTTOM_DISTANCE });
}


void Window::resizeGraphArea(const sf::Vector2u& size)
{
    graphArea[0].setSize({ size.x - 2 * GRAPH_AREA_X_MARGIN, 1 });

    graphArea[1].setSize({ size.x - 2 * GRAPH_AREA_X_MARGIN, 1 });
    graphArea[1].setPosition({ GRAPH_AREA_X_MARGIN, size.y - GRAPH_AREA_Y_MARGIN_BOTTOM });

    graphArea[2].setSize({ 1, size.y - GRAPH_AREA_Y_MARGIN_UP - GRAPH_AREA_Y_MARGIN_BOTTOM });

    graphArea[3].setSize({ 1, size.y  - GRAPH_AREA_Y_MARGIN_UP - GRAPH_AREA_Y_MARGIN_BOTTOM });
    graphArea[3].setPosition({ size.x - GRAPH_AREA_X_MARGIN, GRAPH_AREA_Y_MARGIN_UP });
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

