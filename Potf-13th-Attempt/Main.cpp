#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "PauseMenu.h"
#include "GameWorld.h"
#include "Player.h"
#include "SettingsMenu.h"
// reference: integrating tilemap backgrounds and player animation in sfml explained in sfml sprite documentation (https://www.sfml-dev.org/tutorials/2.5/graphics-sprite.php)

void gameplay(sf::RenderWindow& window, PauseMenu& pauseMenu, GameWorld& gameWorld, Player& player, sf::Text& fpsText, bool& isPaused, int& gameState) {
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

    // draw fps counter
    window.draw(fpsText);

    window.display();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Path of the Foresaken");
    MainMenu menu;
    PauseMenu pauseMenu;
    SettingsMenu settingsMenu;
    GameWorld gameWorld; // instantiate the game world
    Player player; // instantiate the player

    // setup fps counter
    sf::Font font;
    if (!font.loadFromFile("CloisterBlack.ttf"))
        throw std::runtime_error("failed to load font"); // load font for fps text
    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setCharacterSize(20);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(1100, 10); // position top right

    sf::Clock fpsClock;
    int frameCount = 0;
    float elapsedTime = 0.0f;

    int gameState = 0; // 0 for main menu, 1 for gameplay, 2 for settings menu
    bool isPaused = false;

    // set initial FPS limit from settings menu
    int fpsLimit = settingsMenu.getSelectedFPS();
    if (fpsLimit > 0) window.setFramerateLimit(fpsLimit);

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

                // calculate fps
                frameCount++;
                elapsedTime += fpsClock.restart().asSeconds();
                if (elapsedTime >= 1.0f) { // update fps every second
                    fpsText.setString("FPS: " + std::to_string(frameCount));
                    frameCount = 0;
                    elapsedTime = 0.0f;
                }
            }
            gameplay(window, pauseMenu, gameWorld, player, fpsText, isPaused, gameState);
        }
        else if (gameState == 2) { // settings menu
            settingsMenu.handleInput(window, gameState);
            settingsMenu.render(window);

            // update fps limit if changed in settings menu
            fpsLimit = settingsMenu.getSelectedFPS();
            if (fpsLimit > 0) window.setFramerateLimit(fpsLimit);
        }
    }
    return 0;
}