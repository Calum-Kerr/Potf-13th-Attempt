#include<SFML/Graphics.hpp>
#include "MainMenu.h"
// reference: implementing game states in sfml explained in sfml game loop documentation (https://www.sfml-dev.org/tutorials/2.5/start-linux.php)

void gameplay(sf::RenderWindow& window) {
    // placeholder gameplay state
    window.clear(sf::Color::Blue); // blue background for gameplay
    sf::Font font;
    if (!font.loadFromFile("CloisterBlack.ttf"))return; // load font
    sf::Text text;
    text.setFont(font);
    text.setString("Gameplay Placeholder");
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::White);
    text.setPosition(450, 300); // center text
    window.draw(text);
    window.display();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Path of the Foresaken");
    MainMenu menu;
    int gameState = 0; // 0 for menu, 1 for gameplay, 2 for settings

    while (window.isOpen()) {
        if (gameState == 0) { // main menu
            menu.handleInput(window, gameState);
            menu.update();
            menu.render(window);
        }
        else if (gameState == 1) { // gameplay
            gameplay(window);
        }
        else if (gameState == 2) { // settings (not implemented yet)
            window.clear(sf::Color::Green); // green placeholder for settings
            window.display();
        }
    }
    return 0;
}