#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class SettingsMenu {
public:
    SettingsMenu();
    void handleEvent(const sf::Event& event, sf::RenderWindow& window, int& gameState);
    void render(sf::RenderWindow& window);
    int getSelectedFPS();

private:
    sf::Font font;
    sf::Text title;
    std::vector<sf::Text> options;
    std::vector<int> fpsOptions;
    int selectedOption;

    void applySettings(sf::RenderWindow& window);
};