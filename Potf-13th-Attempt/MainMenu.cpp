#include "MainMenu.h"
#include <iostream>
#include <stdexcept>

// constructor initializes main menu and loads font
MainMenu::MainMenu() :selectedOption(0), fpsLimit(60) {
    if (!font.loadFromFile("CloisterBlack.ttf"))
        throw std::runtime_error("failed to load font");

    // setting up the title text
    title.setFont(font);
    title.setString("Path of the Foresaken");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setPosition(200, 100);

    // setting up the options for main menu
    std::vector<std::string> options = { "Start Game", "Continue", "Settings", "Quit" };
    float y = 200;
    for (const auto& opt : options) {
        sf::Text menuText;
        menuText.setFont(font);
        menuText.setString(opt);
        menuText.setCharacterSize(30);
        menuText.setFillColor(sf::Color::White);
        menuText.setPosition(250, y);
        menuOptions.push_back(menuText);
        y += 50;
    }
    menuOptions[selectedOption].setFillColor(sf::Color::Red);

    // initializing fog particles for visual effect
    initFogParticles();
}

// this function initializes fog particles for the background effect
void MainMenu::initFogParticles() {
    for (int i = 0; i < 50; i++) {
        sf::CircleShape particle(3);
        sf::CircleShape glow(6);

        int colorChoice = rand() % 3;
        if (colorChoice == 0) particle.setFillColor(sf::Color(255, 69, 0));
        else if (colorChoice == 1) particle.setFillColor(sf::Color(255, 140, 0));
        else particle.setFillColor(sf::Color(255, 215, 0));

        glow.setFillColor(sf::Color(255, 69, 0, 50));
        glow.setOrigin(3, 3);
        glow.setPosition(rand() % 1280, rand() % 720);

        particle.setOrigin(1.5, 1.5);
        particle.setPosition(glow.getPosition());

        fogParticles.push_back(glow);
        fogParticles.push_back(particle);

        float randomSpeedX = -0.5f - (rand() % 10) * 0.1f;
        float randomSpeedY = 0.1f * (rand() % 3);
        fogSpeeds.push_back(sf::Vector2f(randomSpeedX, randomSpeedY));
    }
}

// this function handles user input and updates the selected option
void MainMenu::handleEvent(const sf::Event& event, sf::RenderWindow& window, int& gameState) {
    if (event.type == sf::Event::Closed) {
        window.close();
    }

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            menuOptions[selectedOption].setFillColor(sf::Color::White);
            selectedOption = (selectedOption - 1 + menuOptions.size()) % menuOptions.size();
            menuOptions[selectedOption].setFillColor(sf::Color::Red);
        }
        else if (event.key.code == sf::Keyboard::Down) {
            menuOptions[selectedOption].setFillColor(sf::Color::White);
            selectedOption = (selectedOption + 1) % menuOptions.size();
            menuOptions[selectedOption].setFillColor(sf::Color::Red);
        }
        else if (event.key.code == sf::Keyboard::Enter) {
            if (selectedOption == 0) {
                gameState = 1; // start game
            }
            else if (selectedOption == 1) {
                // continue - not implemented, could set gameState=1 if you want
            }
            else if (selectedOption == 2) {
                gameState = 2; // go to settings
            }
            else if (selectedOption == 3) {
                window.close(); // quit
            }
        }
    }
}

// this function updates the fog particles for the background effect
void MainMenu::update() {
    for (size_t i = 0; i < fogParticles.size(); i += 2) {
        fogParticles[i].move(fogSpeeds[i / 2]);
        fogParticles[i + 1].move(fogSpeeds[i / 2]);
        if (fogParticles[i].getPosition().x < -10 || fogParticles[i].getPosition().y > 730) {
            fogParticles[i].setPosition(1280, rand() % 720);
            fogParticles[i + 1].setPosition(fogParticles[i].getPosition());
        }
    }
}

// this function renders the main menu on the window
void MainMenu::render(sf::RenderWindow& window) {
    for (const auto& particle : fogParticles)
        window.draw(particle);

    window.draw(title);
    for (const auto& opt : menuOptions)
        window.draw(opt);
}

// this function returns the fps limit
int MainMenu::getFpsLimit() const {
    return fpsLimit;
}
