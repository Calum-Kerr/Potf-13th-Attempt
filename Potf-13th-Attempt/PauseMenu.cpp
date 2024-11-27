#include "PauseMenu.h"
// reference: handling pause states in sfml explained in sfml tutorials (https://www.sfml-dev.org/tutorials/2.5/window-events.php)

PauseMenu::PauseMenu() : selectedOption(0) {
    if (!font.loadFromFile("CloisterBlack.ttf"))throw std::runtime_error("failed to load font");

    title.setFont(font);
    title.setString("Pause Menu");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setPosition(480, 150); // center the title

    // setup menu options
    std::vector<std::string> options = { "Resume","Restart","Quit" };
    float y = 250;
    for (const auto& opt : options) {
        sf::Text menuText;
        menuText.setFont(font);
        menuText.setString(opt);
        menuText.setCharacterSize(30);
        menuText.setFillColor(sf::Color::White);
        menuText.setPosition(520, y); // center each option
        menuOptions.push_back(menuText);
        y += 50;
    }
    menuOptions[selectedOption].setFillColor(sf::Color::Red); // highlight first option
}

void PauseMenu::handleInput(sf::RenderWindow& window, bool& isPaused, int& gameState) {
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
                if (selectedOption == 0)isPaused = false; // resume game
                else if (selectedOption == 1)gameState = 0; // restart to main menu
                else if (selectedOption == 2)window.close(); // quit game
            }
            if (event.key.code == sf::Keyboard::Escape) {
                isPaused = false; // unpause with Esc
            }
        }
    }
}

void PauseMenu::render(sf::RenderWindow& window) {
    for (const auto& opt : menuOptions)window.draw(opt); // draw menu options
    window.draw(title); // draw title
}