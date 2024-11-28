#pragma once
#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class SettingsMenu {
private:
    sf::Font font;
    sf::Text title;
    std::vector<sf::Text> options;
    int selectedOption;

    std::vector<int> fpsOptions; // stores FPS options like 60, 90, etc.

public:
    SettingsMenu();
    void handleInput(sf::RenderWindow& window, int& gameState); // navigate options
    void render(sf::RenderWindow& window); // draw menu
    int getSelectedFPS(); // get selected FPS
};

#endif