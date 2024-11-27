#include<SFML/Graphics.hpp>
#include "MainMenu.h"
#include "PauseMenu.h"
// reference: creating game loop and pause states in sfml (https://www.sfml-dev.org/tutorials/2.5/start-linux.php)

void gameplay(sf::RenderWindow& window, bool& isPaused, PauseMenu& pauseMenu, int& gameState) {
    // placeholder gameplay
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

    // if paused, render pause menu
    if (isPaused) {
        pauseMenu.handleInput(window, isPaused, gameState);
        pauseMenu.render(window);
    }
    window.display();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Path of the Foresaken");
    MainMenu menu;
    PauseMenu pauseMenu;
    int gameState = 0; // 0 for menu, 1 for gameplay
    bool isPaused = false;

    while (window.isOpen()) {
        if (gameState == 0) { // main menu
            menu.handleInput(window, gameState);
            menu.update();
            menu.render(window);
        }
        else if (gameState == 1) { // gameplay
            if (!isPaused) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)window.close();
                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                        isPaused = true; // pause game with Esc
                    }
                }
            }
            gameplay(window, isPaused, pauseMenu, gameState);
        }
    }
    return 0;
}