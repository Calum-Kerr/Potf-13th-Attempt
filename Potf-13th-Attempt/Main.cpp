#include <SFML/Graphics.hpp>
#include <iostream>
#include "MainMenu.h"
#include "PauseMenu.h"
#include "GameWorld.h"
#include "Player.h"
#include "SettingsMenu.h"

// this function handles the gameplay rendering and updates
void gameplay(sf::RenderWindow& window, PauseMenu& pauseMenu, GameWorld& gameWorld, Player& player, sf::Text& fpsText, bool& isPaused, int& gameState, float deltaTime) {
    std::cout << "entering gameplay function" << std::endl;

    // render gameplay background
    gameWorld.render(window);
    std::cout << "rendered game world" << std::endl;

    // update and render the player
    player.update(gameWorld, deltaTime);
    player.render(window);
    std::cout << "updated and rendered player" << std::endl;

    // if paused, just render pause menu on top
    if (isPaused) {
        std::cout << "game is paused" << std::endl;
        pauseMenu.render(window);
        std::cout << "rendered pause menu" << std::endl;
    }

    // draw fps counter
    window.draw(fpsText);
    std::cout << "drew fps counter" << std::endl;
}

int main() {
    std::cout << "starting main function" << std::endl;
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Path of the Foresaken");
    MainMenu menu;
    PauseMenu pauseMenu;
    SettingsMenu settingsMenu;
    GameWorld gameWorld;
    Player player;
    int gameState = 0; // 0: main menu, 1: game, 2: settings menu

    // setup fps counter
    sf::Font font;
    if (!font.loadFromFile("CloisterBlack.ttf"))
        throw std::runtime_error("failed to load font");
    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setCharacterSize(20);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(1100, 10);

    bool isPaused = false;

    // set initial fps limit from settings menu
    int fpsLimit = settingsMenu.getSelectedFPS();
    if (fpsLimit > 0) window.setFramerateLimit(fpsLimit);

    sf::Clock deltaClock;
    float deltaTime = 0.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // global events
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // state-specific event handling
            if (gameState == 0) {
                // main menu
                menu.handleEvent(event, window, gameState);
            }
            else if (gameState == 1) {
                // gameplay
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    // toggle pause if in gameplay
                    isPaused = !isPaused;
                    std::cout << "toggled pause state: " << isPaused << std::endl;
                }

                // if paused, pass events to pause menu
                if (isPaused) {
                    pauseMenu.handleEvent(event, window, isPaused, gameState);
                }
            }
            else if (gameState == 2) {
                // settings menu
                settingsMenu.handleEvent(event, window, gameState);
            }
        }

        // calculate delta time
        deltaTime = deltaClock.restart().asSeconds();
        std::cout << "delta time: " << deltaTime << std::endl;

        window.clear();
        std::cout << "window cleared" << std::endl;

        // update and render based on gameState
        if (gameState == 0) {
            // main menu
            std::cout << "in main menu" << std::endl;
            menu.update();
            menu.render(window);
            std::cout << "rendered main menu" << std::endl;
        }
        else if (gameState == 1) {
            // gameplay
            std::cout << "in gameplay" << std::endl;
            if (!isPaused) {
                player.update(gameWorld, deltaTime);
                gameWorld.update(deltaTime);
                std::cout << "updated game logic" << std::endl;
            }
            gameplay(window, pauseMenu, gameWorld, player, fpsText, isPaused, gameState, deltaTime);
            std::cout << "rendered gameplay" << std::endl;
        }
        else if (gameState == 2) {
            // settings menu
            std::cout << "in settings menu" << std::endl;
            settingsMenu.render(window);
            std::cout << "rendered settings menu" << std::endl;

            // update fps limit if changed in settings
            int fpsLimit = settingsMenu.getSelectedFPS();
            if (fpsLimit > 0)
                window.setFramerateLimit(fpsLimit);
            gameWorld.update(deltaTime);
            std::cout << "updated game world logic in settings menu" << std::endl;
        }

        window.display();
        std::cout << "window displayed" << std::endl;
    }
    std::cout << "exiting main function" << std::endl;
    return 0;
}