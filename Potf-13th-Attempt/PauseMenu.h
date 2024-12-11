#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class PauseMenu {
public:
    PauseMenu();
    void handleEvent(const sf::Event& event, sf::RenderWindow& window, bool& isPaused, int& gameState);
    void render(sf::RenderWindow& window);

private:
    sf::Font font;
    sf::Text title;
    std::vector<sf::Text> menuOptions;
    int selectedOption;
    sf::RectangleShape background;
};