#include "PauseMenu.h"
#include <iostream>
#include <stdexcept>

// constructor initializes pause menu and loads font
PauseMenu::PauseMenu() {
    std::cout << "initializing pause menu" << std::endl;
    if (!font.loadFromFile("CloisterBlack.ttf"))
        throw std::runtime_error("failed to load font");

    // setting up the title text
    title.setFont(font);
    title.setString("Paused");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setPosition(200, 100);

    // setting up the options for pause menu
    std::vector<std::string> optionStrings = { "Resume", "Main Menu", "Exit" };
    float y = 200;
    selectedOption = 0;
    for (const auto& opt : optionStrings) {
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

    // setting up the background
    background.setSize(sf::Vector2f(1280, 720));
    background.setFillColor(sf::Color(0, 0, 0, 150));
    std::cout << "pause menu initialized" << std::endl;
}

// this function handles user input and updates the selected option
void PauseMenu::handleEvent(const sf::Event& event, sf::RenderWindow& window, bool& isPaused, int& gameState) {
    std::cout << "handling input in pause menu" << std::endl;

    if (event.type == sf::Event::Closed)
        window.close();

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            menuOptions[selectedOption].setFillColor(sf::Color::White);
            selectedOption = (selectedOption - 1 + menuOptions.size()) % menuOptions.size();
            menuOptions[selectedOption].setFillColor(sf::Color::Red);
            std::cout << "selected option: " << selectedOption << std::endl;
        }
        else if (event.key.code == sf::Keyboard::Down) {
            menuOptions[selectedOption].setFillColor(sf::Color::White);
            selectedOption = (selectedOption + 1) % menuOptions.size();
            menuOptions[selectedOption].setFillColor(sf::Color::Red);
            std::cout << "selected option: " << selectedOption << std::endl;
        }
        else if (event.key.code == sf::Keyboard::Enter) {
            if (selectedOption == 0) { // resume
                isPaused = false;
                std::cout << "resumed game" << std::endl;
            }
            else if (selectedOption == 1) { // main menu
                gameState = 0;
                std::cout << "game state changed to: " << gameState << std::endl;
            }
            else if (selectedOption == 2) { // exit
                window.close();
                std::cout << "window closed" << std::endl;
            }
        }
    }
}

// this function renders the pause menu on the window
void PauseMenu::render(sf::RenderWindow& window) {
    std::cout << "rendering pause menu" << std::endl;
    window.draw(background);
    window.draw(title);
    for (const auto& opt : menuOptions)
        window.draw(opt);
    std::cout << "pause menu rendered" << std::endl;
}