
#include <iostream>
#include <string>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

#include "window.h"
#include "config.h"

constexpr float menu_A_x_begin = 0;
constexpr float menu_A_x_end = 80;
constexpr float menu_A_y_begin = 80;
constexpr float menu_A_y_end = 80;


Window::Window()
{
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode({ 1400, 900 }, sf::Style::Titlebar ) , "", sf::State::Windowed, settings);
}


void Window::init()
{
    prepareMainMenu();
    prepareTexts();
    hold.isHeld = false;
}


void Window::run()
{
    while(window->isOpen()) {
        while(const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window->close();
                continue;
            }
            if (event->is<sf::Event::MouseButtonPressed>()) {
                sf::Vector2i position = sf::Mouse::getPosition(*window);
                if (position.x <= 80.f && position.y <= 20.f) {
                    drawCircle(20, 10, 20);
                    continue;
                }
                auto [index, shiftX, shiftY] = isMouseOverCircle(position);
                if (index >= 0) {
                    hold = { true, index, shiftX, shiftY };
                }
                continue;
            }
            if (event->is<sf::Event::MouseButtonReleased>()) {
                hold = { false, -1, 0, 0 };
                continue;
            }
            if (event->is<sf::Event::MouseMoved>() && hold.isHeld) {
                auto mouseEvent = event.value().getIf<sf::Event::MouseMoved>();
                float x = mouseEvent->position.x;
                float y = mouseEvent->position.y;
                float radius = circles[hold.index].getRadius();
                circles[hold.index].setPosition({ x - radius - hold.shiftX, y - radius - hold.shiftY });
                continue;
            }
        }
        window->clear(sf::Color::Red);

        for (const auto& menu : menus) {
            window->draw(menu);
        }
        for (const auto& title : titles) {
            window->draw(title);
        }
        for (const auto& circle : circles) {
            window->draw(circle);
        }
        window->display();
    }
}


void Window::drawCircle(float radius, float x, float y)
{
    sf::CircleShape circle(radius, 100);
    circle.setPosition({x, y});
    circle.setFillColor(sf::Color::Blue);
    circles.push_back(circle);
}


void Window::prepareMainMenu()
{
    menus.emplace_back( sf::Vector2f{ 80.f, 20.f });
    menus[0].setPosition({ 0.f, 0.f });
    menus[0].setFillColor(sf::Color::White);

    menus.emplace_back( sf::Vector2f{ 80.f, 20.f });
    menus[1].setPosition({ 80.f, 0.f });
    menus[1].setFillColor(sf::Color::White);
}


void Window::prepareTexts()
{
    if (!font.openFromFile(std::string(RESOURCES) + "Arial.ttf")) {
        return;
    }

    titles.emplace_back(font, "Add Node", 15);
    titles[0].setFillColor(sf::Color::Black);
    titles[0].setPosition({ 10.f, 2.f });

    titles.emplace_back(font, "Add Line", 15);
    titles[1].setFillColor(sf::Color::Black);
    titles[1].setPosition({ 90.f, 2.f });
}


std::tuple<int, float, float> Window::isMouseOverCircle(const sf::Vector2i& mousePos)
{
    for (size_t i = 0; i < circles.size(); i++) {
        float radius = circles[i].getRadius();
        sf::Vector2f circlePos = circles[i].getPosition();
        float circleCenterX = circlePos.x + radius;
        float circleCenterY = circlePos.y + radius;
        float shiftX = mousePos.x - circleCenterX;
        float shiftY = mousePos.y - circleCenterY;
        int distance = sqrt(pow(shiftX, 2) + pow(shiftY, 2));
        if (distance <= radius) {
            return { i, shiftX, shiftY };
        }
    }
    return { -1, 0, 0 };
}

