// #include "src/Game.h"

// int main()
// {
//     Game game;

//     return 0;
// }


#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML 3.0 Test");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
