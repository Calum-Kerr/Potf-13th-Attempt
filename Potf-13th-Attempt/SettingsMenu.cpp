#include "SettingsMenu.h"
#include <iostream>
#include <stdexcept>

// constructor initializes settings menu and loads font
SettingsMenu::SettingsMenu() :selectedOption(0) {
    std::cout << "initializing settings menu" << std::endl;
    if (!font.loadFromFile("CloisterBlack.ttf"))
        throw std::runtime_error("failed to load font");

    // setting up the title text
    title.setFont(font);
    title.setString("Settings");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setPosition(200, 100);

    // setting up the options for fps settings
    std::vector<std::string> optionStrings = { "60 FPS", "90 FPS", "120 FPS" };
    fpsOptions = { 60, 90, 120 };
    float y = 200;
    for (const auto& opt : optionStrings) {
        sf::Text menuText;
        menuText.setFont(font);
        menuText.setString(opt);
        menuText.setCharacterSize(30);
        menuText.setFillColor(sf::Color::White);
        menuText.setPosition(250, y);
        options.push_back(menuText);
        y += 50;
    }
    options[selectedOption].setFillColor(sf::Color::Red);
    std::cout << "settings menu initialized" << std::endl;
}

// this function handles user input and updates the selected option
void SettingsMenu::handleEvent(const sf::Event& event, sf::RenderWindow& window, int& gameState) {
    std::cout << "handling input in settings menu" << std::endl;

    if (event.type == sf::Event::Closed) window.close();
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            options[selectedOption].setFillColor(sf::Color::White);
            selectedOption = (selectedOption - 1 + options.size()) % options.size();
            options[selectedOption].setFillColor(sf::Color::Red);
            std::cout << "selected option: " << selectedOption << std::endl;
        }
        else if (event.key.code == sf::Keyboard::Down) {
            options[selectedOption].setFillColor(sf::Color::White);
            selectedOption = (selectedOption + 1) % options.size();
            options[selectedOption].setFillColor(sf::Color::Red);
            std::cout << "selected option: " << selectedOption << std::endl;
        }
        else if (event.key.code == sf::Keyboard::Enter) {
            applySettings(window);
            gameState = 0; // return to main menu
            std::cout << "game state changed to: " << gameState << std::endl;
        }
    }
}

// this function renders the settings menu on the window
void SettingsMenu::render(sf::RenderWindow& window) {
    std::cout << "rendering settings menu" << std::endl;
    window.clear();
    window.draw(title);
    for (const auto& opt : options)
        window.draw(opt);
    window.display();
    std::cout << "settings menu rendered" << std::endl;
}

// this function returns the selected fps option
int SettingsMenu::getSelectedFPS() {
    std::cout << "getting selected fps: " << fpsOptions[selectedOption] << std::endl;
    return fpsOptions[selectedOption];
}

// this function applies the selected fps setting to the window
void SettingsMenu::applySettings(sf::RenderWindow& window) {
    int selectedFPS = getSelectedFPS();
    window.setFramerateLimit(selectedFPS);
    std::cout << "applied settings: " << selectedFPS << " fps" << std::endl;
}