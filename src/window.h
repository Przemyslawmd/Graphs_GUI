
#include <memory>

#include <SFML/Graphics.hpp>


class Window
{
public:
    Window();

    void run();

private:
    std::unique_ptr<sf::RenderWindow> window;
};

