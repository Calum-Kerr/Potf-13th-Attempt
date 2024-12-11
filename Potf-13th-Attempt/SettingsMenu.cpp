#include "SettingsMenu.h"

// reference: creating text-based menus with sfml explained in the sfml text tutorial (https://www.sfml-dev.org/tutorials/2.5/graphics-text.php)

SettingsMenu::SettingsMenu() : selectedOption(0) {
    if (!font.loadFromFile("CloisterBlack.ttf"))
        throw std::runtime_error("failed to load font");

    title.setFont(font);
    title.setString("Settings");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setPosition(400, 100);

    // initialize fps options
    fpsOptions = { 60, 90, 120, 144, 0 }; // 0 for uncapped
    std::vector<std::string> fpsStrings = { "60 FPS", "90 FPS", "120 FPS", "144 FPS", "Uncapped" };

    float y = 200;
    for (const auto& fpsString : fpsStrings) {
        sf::Text option;
        option.setFont(font);
        option.setString(fpsString);
        option.setCharacterSize(30);
        option.setFillColor(sf::Color::White);
        option.setPosition(400, y);
        options.push_back(option);
        y += 50;
    }
    options[selectedOption].setFillColor(sf::Color::Red); // highlight first option
}

void SettingsMenu::handleInput(sf::RenderWindow& window, int& gameState) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                options[selectedOption].setFillColor(sf::Color::White);
                selectedOption = (selectedOption - 1 + options.size()) % options.size();
                options[selectedOption].setFillColor(sf::Color::Red);
            }
            if (event.key.code == sf::Keyboard::Down) {
                options[selectedOption].setFillColor(sf::Color::White);
                selectedOption = (selectedOption + 1) % options.size();
                options[selectedOption].setFillColor(sf::Color::Red);
            }
            if (event.key.code == sf::Keyboard::Enter) {
                gameState = 0; // return to main menu
            }
        }
    }
}

void SettingsMenu::render(sf::RenderWindow& window) {
    window.clear();
    window.draw(title);
    for (const auto& option : options)
        window.draw(option);
    window.display();
}

int SettingsMenu::getSelectedFPS() {
    return fpsOptions[selectedOption];
}

