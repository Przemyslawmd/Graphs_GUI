
#include <iostream>

#include <SFML/System/Vector2.hpp>

#include "window.h"


Window::Window()
{
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode({ 800, 600 }, sf::Style::Titlebar ) , "", sf::State::Windowed, settings);
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
            }
        }
        window->clear(sf::Color::Red);
        
        //sf::CircleShape cirle_1(20.f, 100);
        //cirle_1.setFillColor(sf::Color::Blue);
        //cirle_1.setPosition({10.f, 20.f});
        
        //sf::CircleShape cirle_2(20.f, 100);
        //cirle_2.setFillColor(sf::Color::Green);
        //cirle_2.setPosition({50.f, 100.f});
        
        sf::RectangleShape rect_1({ 80.f, 20.f });
        rect_1.setFillColor(sf::Color::White);
        rect_1.setPosition({0.f, 0.f});

        sf::RectangleShape rect_2({ 80.f, 20.f });
        rect_2.setFillColor(sf::Color::White);
        rect_2.setPosition({80.f, 0.f});

        for (const auto& shape : shapes) {
            window->draw(shape);
        }
        window->draw(rect_1);
        window->draw(rect_2);
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

