#include "MainMenu.h"
#include <iostream>
// reference: creating glow effects using sfml shape properties (https://www.sfml-dev.org/tutorials/2.5/graphics-shape.php)

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

    initFogParticles(); // initialize glowing embers
}

void MainMenu::initFogParticles() {
    for (int i = 0;i < 50;i++) { // 50 particles
        sf::CircleShape particle(3); // small ember
        sf::CircleShape glow(6);     // larger "halo" for glow

        // assign ember color
        int colorChoice = rand() % 3; // randomly choose red, orange, or yellow
        if (colorChoice == 0) particle.setFillColor(sf::Color(255, 69, 0)); // red-orange
        else if (colorChoice == 1) particle.setFillColor(sf::Color(255, 140, 0)); // orange
        else particle.setFillColor(sf::Color(255, 215, 0)); // yellow

        // configure glow
        glow.setFillColor(sf::Color(255, 69, 0, 50)); // semi-transparent red glow
        glow.setOrigin(3, 3); // centre glow
        glow.setPosition(rand() % 1280, rand() % 720); // random position

        // set ember position
        particle.setOrigin(1.5, 1.5); // centre ember
        particle.setPosition(glow.getPosition()); // same as glow

        // store both in fogParticles
        fogParticles.push_back(glow);
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
    // animate embers and their glow
    for (size_t i = 0;i < fogParticles.size();i += 2) { // every 2 particles (glow + ember)
        fogParticles[i].move(-0.8, 0.3);       // glow particle
        fogParticles[i + 1].move(-0.8, 0.3);    // ember particle
        if (fogParticles[i].getPosition().x < -10 || fogParticles[i].getPosition().y > 730) { // loop back
            fogParticles[i].setPosition(1280, rand() % 720);
            fogParticles[i + 1].setPosition(fogParticles[i].getPosition());
        }
    }
}

void MainMenu::render(sf::RenderWindow& window) {
    window.clear();

    // draw ember particles with their glow
    for (const auto& particle : fogParticles)
        window.draw(particle);

    window.draw(title);
    for (const auto& opt : menuOptions)window.draw(opt);
    window.display();
}
