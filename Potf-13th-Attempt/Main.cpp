#include<SFML/Graphics.hpp>
// reference: official sfml tutorial for window creation (https://www.sfml-dev.org/tutorials/2.5/start-linux.php)
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Path of the Foresaken");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)window.close();
        }
        window.clear();
        window.display();
    }
    return 0;
}