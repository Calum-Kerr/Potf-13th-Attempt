#include <SFML/Graphics.hpp>
#include <iostream>
#include "MainMenu.h"
#include "PauseMenu.h"
#include "GameWorld.h"
#include "Player.h"
#include "SettingsMenu.h"
#include "Enemy.h" // include the new Enemy class

void resetGame(Player& player, Enemy& enemy, int& gameState) {
    player.reset();
    enemy.reset();
    gameState = 1; // remain in gameplay
}

void gameplay(sf::RenderWindow& window, PauseMenu& pauseMenu, GameWorld& gameWorld, Player& player, Enemy& enemy, sf::Text& fpsText, bool& isPaused, int& gameState, float deltaTime) {
    std::cout << "entering gameplay function" << std::endl;

    gameWorld.render(window);
    std::cout << "rendered game world" << std::endl;

    player.update(gameWorld, deltaTime);
    player.render(window);
    std::cout << "updated and rendered player" << std::endl;

    enemy.update(gameWorld, deltaTime, player);
    enemy.render(window);
    bool enemyAttackFinished = false;
    // check if enemy attack finished:
    if (enemy.getAndClearAttackFinished()) {
        // check distance
        sf::FloatRect pBounds = player.getSpriteBounds();
        sf::FloatRect eBounds = enemy.getBounds();
        float pxCenter = pBounds.left + pBounds.width * 0.5f;
        float exCenter = eBounds.left + eBounds.width * 0.5f;
        float dist = std::fabs(pxCenter - exCenter);
        if (dist < 100.0f && !enemy.isDead() && !player.isDead()) {
            player.takeDamage(1);
            std::cout << "Enemy hit player! Player health reduced." << std::endl;
        }
    }

    if (isPaused) {
        std::cout << "game is paused" << std::endl;
        pauseMenu.render(window);
        std::cout << "rendered pause menu" << std::endl;
    }

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
    Enemy enemy;
    int gameState = 0; // 0: main menu, 1: game, 2: settings

    sf::Font font;
    if (!font.loadFromFile("CloisterBlack.ttf"))
        throw std::runtime_error("failed to load font");
    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setCharacterSize(20);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(1100, 10);

    bool isPaused = false;
    int fpsLimit = settingsMenu.getSelectedFPS();
    if (fpsLimit > 0) window.setFramerateLimit(fpsLimit);

    sf::Clock deltaClock;
    float deltaTime = 0.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (gameState == 0) {
                menu.handleEvent(event, window, gameState);
            }
            else if (gameState == 1) {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    isPaused = !isPaused;
                    std::cout << "toggled pause state: " << isPaused << std::endl;
                }
                if (isPaused) {
                    pauseMenu.handleEvent(event, window, isPaused, gameState);
                }
            }
            else if (gameState == 2) {
                settingsMenu.handleEvent(event, window, gameState);
            }
        }

        deltaTime = deltaClock.restart().asSeconds();
        std::cout << "delta time: " << deltaTime << std::endl;

        window.clear();
        std::cout << "window cleared" << std::endl;

        if (gameState == 0) {
            std::cout << "in main menu" << std::endl;
            menu.update();
            menu.render(window);
            std::cout << "rendered main menu" << std::endl;
        }
        else if (gameState == 1) {
            std::cout << "in gameplay" << std::endl;
            if (!isPaused) {
                player.update(gameWorld, deltaTime);
                enemy.update(gameWorld, deltaTime, player);
                gameWorld.update(deltaTime);
                std::cout << "updated game logic" << std::endl;

                // press H to hurt player
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
                    player.takeDamage(1);
                }

                // check deaths
                if (player.isDead() || enemy.isDead()) {
                    std::cout << "someone died, resetting game." << std::endl;
                    resetGame(player, enemy, gameState);
                }
            }
            gameplay(window, pauseMenu, gameWorld, player, enemy, fpsText, isPaused, gameState, deltaTime);
            std::cout << "rendered gameplay" << std::endl;
        }
        else if (gameState == 2) {
            std::cout << "in settings menu" << std::endl;
            settingsMenu.render(window);
            std::cout << "rendered settings menu" << std::endl;

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