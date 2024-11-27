#include "MainMenu.h"
#include <iostream> // for printing messages to console
// reference: handling key events in sfml explained in sfml documentation (https://www.sfml-dev.org/tutorials/2.5/window-events.php)

MainMenu::MainMenu() : selectedOption(0) {
    if (!font.loadFromFile("CloisterBlack.ttf"))throw std::runtime_error("failed to load font");

    title.setFont(font);
    title.setString("Path of the Foresaken");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setPosition(200, 100);

    // setup menu options
    std::vector<std::string> options = { "Start Game","Continue","Settings","Quit" };
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
    menuOptions[selectedOption].setFillColor(sf::Color::Red); // highlight first option
}

void MainMenu::handleInput(sf::RenderWindow& window, int& gameState) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)window.close();
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                menuOptions[selectedOption].setFillColor(sf::Color::White);
                selectedOption = (selectedOption - 1 + menuOptions.size()) % menuOptions.size();
                menuOptions[selectedOption].setFillColor(sf::Color::Red);
            }
            if (event.key.code == sf::Keyboard::Down) {
                menuOptions[selectedOption].setFillColor(sf::Color::White);
                selectedOption = (selectedOption + 1) % menuOptions.size();
                menuOptions[selectedOption].setFillColor(sf::Color::Red);
            }
            if (event.key.code == sf::Keyboard::Enter) {
                if (selectedOption == 0)std::cout << "Start Game Selected" << std::endl;
                else if (selectedOption == 1)std::cout << "Continue Selected" << std::endl;
                else if (selectedOption == 2)std::cout << "Settings Selected" << std::endl;
                else if (selectedOption == 3)window.close(); // quit game
            }
        }
    }
}

void MainMenu::update() {
    // no updates yet
}

void MainMenu::render(sf::RenderWindow& window) {
    window.clear();
    window.draw(title);
    for (const auto& opt : menuOptions)window.draw(opt);
    window.display();
}