#include<SFML/Graphics.hpp>
#include "MainMenu.h"
// reference: updating window size explained in sfml tutorial for video modes (https://www.sfml-dev.org/tutorials/2.5/window-window.php)

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Path of the Foresaken"); // updated to 1280x720
    MainMenu menu;

    while (window.isOpen()) {
        menu.handleInput(window);
        menu.update();
        menu.render(window);
    }
    return 0;
}