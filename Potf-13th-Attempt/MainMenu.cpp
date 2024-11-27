#include "MainMenu.h"
// reference: sfml tutorial on managing fonts and rendering text (https://www.sfml-dev.org/tutorials/2.5/graphics-text.php)

MainMenu::MainMenu() : selectedOption(0) {
    if (!font.loadFromFile("CloisterBlack.ttf"))throw std::runtime_error("failed to load font");

    title.setFont(font);
    title.setString("Path of the Foresaken");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setPosition(200, 100); // position title

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
        y += 50; // position menu options
    }
    menuOptions[selectedOption].setFillColor(sf::Color::Red); // highlight first option
}

void MainMenu::handleInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)window.close();
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                menuOptions[selectedOption].setFillColor(sf::Color::White); // reset color
                selectedOption = (selectedOption - 1 + menuOptions.size()) % menuOptions.size(); // move up
                menuOptions[selectedOption].setFillColor(sf::Color::Red); // highlight new
            }
            if (event.key.code == sf::Keyboard::Down) {
                menuOptions[selectedOption].setFillColor(sf::Color::White); // reset color
                selectedOption = (selectedOption + 1) % menuOptions.size(); // move down
                menuOptions[selectedOption].setFillColor(sf::Color::Red); // highlight new
            }
        }
    }
}

void MainMenu::update() {
    // no updates needed yet
}

void MainMenu::render(sf::RenderWindow& window) {
    window.clear();
    window.draw(title); // draw title
    for (const auto& opt : menuOptions)window.draw(opt); // draw menu options
    window.display();
}