
#include <iostream>

#include <SFML/Window.hpp>


int main(void)
{
    sf::Window window(sf::VideoMode({ 800, 600 }), "My Window");
    
    while(window.isOpen()) {
        while(const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
    }
    return 0;
}

