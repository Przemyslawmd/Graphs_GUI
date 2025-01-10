
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
}


void Window::run()
{
    while(window->isOpen()) {
        while(const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window->close();
            }
            if (event->is<sf::Event::MouseButtonPressed>()) {
                sf::Vector2i position = sf::Mouse::getPosition(*window);
                if (position.x <= 80.f && position.y <= 20.f) {
                    drawCircle(20, 10, 20);
                }
                int x = isMouseOverCircle(position);
                if (x >= 0) {
                    std::cout << "Mouse is over circle" << std::endl;
                }

            }
        }
        window->clear(sf::Color::Red);

        for (const auto& menu : menus) {
            window->draw(menu);
        }
        for (const auto& title : titles) {
            window->draw(title);
        }
        for (const auto& shape : shapes) {
            window->draw(shape);
        }
        window->display();
    }
}


void Window::drawCircle(float radius, float x, float y)
{
    sf::CircleShape circle(radius, 100);
    circle.setPosition({x, y});
    circle.setFillColor(sf::Color::Blue);
    shapes.push_back(circle);
}


void Window::prepareMainMenu()
{
    menus.emplace_back( sf::Vector2f{ 80.f, 20.f });
    menus[0].setPosition({ 0.f, 0.f });
    menus[0].setFillColor(sf::Color::White);
}


void Window::prepareTexts()
{
    if (!font.openFromFile(std::string(RESOURCES) + "Arial.ttf")) {
        return;
    }

    titles.emplace_back(font, "Add Node", 15);
    titles[0].setFillColor(sf::Color::Black);
    titles[0].setPosition({ 10.f, 2.f });
}


int Window::isMouseOverCircle(const sf::Vector2i& mousePos)
{
    for (size_t i = 0; i < shapes.size(); i++) {
        float radius = shapes[i].getRadius();
        sf::Vector2f shapePos = shapes[i].getPosition();
        float shapeCenterX = shapePos.x + radius;
        float shapeCenterY = shapePos.y + radius;
        float distanceX = mousePos.x - shapeCenterX;
        float distanceY = mousePos.y - shapeCenterY;
        int distance = sqrt(pow(distanceX, 2) + pow(distanceY, 2));
        if (distance <= radius) {
            return i;
        }
    }
    return -1;
}

