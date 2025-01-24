
#include <string>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

#include "config.h"
#include "menu.h"
#include "window.h"

constexpr size_t initialCircleX = 10;
constexpr size_t initialCircleY = 30;


Window::Window()
{
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode({ 1400, 900 }, sf::Style::Titlebar ) , "", sf::State::Windowed, settings);
}


void Window::init()
{
    prepareMenu();
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
        }
        window->clear(sf::Color::White);

        for (const auto& menu : menus) {
            window->draw(menu);
        }
        for (const auto& title : titles) {
            window->draw(title);
        }
        for (const auto& circle : circles) {
            window->draw(circle.shape);
        }
        window->display();
    }
}


void Window::handleMousePress()
{
    sf::Vector2i position = sf::Mouse::getPosition(*window);
    if (isAddNodeMenu(position)) {
        createCircle(20);
        return;
    }
    auto [index, shiftX, shiftY] = isMouseOverCircle(position);
    if (index >= 0) {
        hold = { true, false, index, shiftX, shiftY };
    }
}


void Window::handleMouseRelease()
{
    if (hold.isMoved) {
        return;
    }

    auto& shape = circles[hold.index].shape;
    if (circles[hold.index].isIndicated == false) {
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(3.0f);
        circles[hold.index].isIndicated = true;
    }
    else if (circles[hold.index].isIndicated == true) {
        shape.setOutlineThickness(0);
        circles[hold.index].isIndicated = false;
    }
}


void Window::handleMouseMove(const std::optional<sf::Event> event)
{
    auto mouseEvent = event.value().getIf<sf::Event::MouseMoved>();
    float x = mouseEvent->position.x;
    float y = mouseEvent->position.y;
    float radius = circles[hold.index].shape.getRadius();
    circles[hold.index].shape.setPosition({ x - radius - hold.shiftX, y - radius - hold.shiftY });
    hold.isMoved = true;
}


void Window::createCircle(float radius)
{
    auto& circle = circles.emplace_back(Circle{ sf::CircleShape{ radius, 100 }, false });
    circle.shape.setPosition({ initialCircleX, initialCircleY });
    circle.shape.setFillColor({ 51, 153, 255 });
}


void Window::prepareMenu()
{
    if (!font.openFromFile(std::string(RESOURCES) + "Arial.ttf")) {
        return;
    }

    for (const auto& [key, value] : Menu) {
        auto& menu = menus.emplace_back( sf::Vector2f{ value.width, value.height });
        menu.setPosition({ value.posX, value.posY });
        menu.setFillColor(sf::Color::White);
        auto& title = titles.emplace_back(font, value.title, 15);
        title.setFillColor(sf::Color::Black);
        title.setPosition({ value.posX + 10.f, value.posY + 2.f });
    }
}


std::tuple<int, float, float> Window::isMouseOverCircle(const sf::Vector2i& mousePos)
{
    for (size_t i = 0; i < circles.size(); i++) {
        const auto& shape = circles[i].shape;
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

