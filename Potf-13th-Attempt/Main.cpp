#include<SFML/Graphics.hpp>
#include "MainMenu.h"
// reference: creating game states explained in sfml tutorials (https://www.sfml-dev.org/tutorials/2.5/window-events.php)

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Path of the Foresaken");
    MainMenu menu;
    int gameState = 0; // 0 for menu, 1 for gameplay, etc.

    while (window.isOpen()) {
        menu.handleInput(window, gameState);
        menu.update();
        menu.render(window);
    }
    return 0;
}