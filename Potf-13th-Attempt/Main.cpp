#include<SFML/Graphics.hpp>
#include "MainMenu.h"
#include "PauseMenu.h"
#include "GameWorld.h"
#include "Player.h"
// reference: integrating tilemap backgrounds and player animation in sfml explained in sfml sprite documentation (https://www.sfml-dev.org/tutorials/2.5/graphics-sprite.php)

void gameplay(sf::RenderWindow& window, bool& isPaused, PauseMenu& pauseMenu, GameWorld& gameWorld, Player& player, int& gameState) {
    // render gameplay background
    window.clear();
    gameWorld.render(window); // draw the tilemap background

    // update and render the player
    player.update(gameWorld); // pass GameWorld for collision detection
    player.render(window);

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
    GameWorld gameWorld; // instantiate the game world
    Player player; // instantiate the player
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
                    if (event.type == sf::Event::Closed) window.close();
                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                        isPaused = true; // pause game with Esc
                    }
                }
            }
            gameplay(window, isPaused, pauseMenu, gameWorld, player, gameState);
        }
    }
    return 0;
}