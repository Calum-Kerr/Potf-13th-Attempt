#include<SFML/Graphics.hpp>
#include "MainMenu.h"
// reference: creating a game loop and integrating classes in sfml (https://www.sfml-dev.org/tutorials/2.5/start-linux.php)

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Path of the Foresaken");
    MainMenu menu;

    while (window.isOpen()) {
        menu.handleInput(window);
        menu.update();
        menu.render(window);
    }
    return 0;
}