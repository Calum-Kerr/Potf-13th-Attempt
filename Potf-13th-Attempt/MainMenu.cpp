#include "MainMenu.h"
#include <iostream>
// reference: animating particles explained in sfml vertex array tutorial (https://www.sfml-dev.org/tutorials/2.5/graphics-vertex-array.php)

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

    initFogParticles(); // initialize fog particles
}

void MainMenu::initFogParticles() {
    for (int i = 0;i < 50;i++) { // 50 particles
        sf::CircleShape particle(5); // small circle as a particle
        particle.setFillColor(sf::Color(255, 255, 255, 50)); // semi-transparent white
        particle.setPosition(rand() % 1280, rand() % 720); // random position
        fogParticles.push_back(particle);
    }
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
                if (selectedOption == 0)gameState = 1; // start game
                else if (selectedOption == 2)gameState = 2; // settings
                else if (selectedOption == 3)window.close(); // quit
            }
        }
    }
}

void MainMenu::update() {
    // animate fog particles
    for (auto& particle : fogParticles) {
        particle.move(-0.5, 0); // move left
        if (particle.getPosition().x < -10) // loop back when off-screen
            particle.setPosition(1280, rand() % 720);
    }
}

void MainMenu::render(sf::RenderWindow& window) {
    window.clear();

    // draw fog particles
    for (const auto& particle : fogParticles)
        window.draw(particle);

    window.draw(title);
    for (const auto& opt : menuOptions)window.draw(opt);
    window.display();
}