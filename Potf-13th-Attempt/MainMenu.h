#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class MainMenu {
public:
    MainMenu();
    void handleEvent(const sf::Event& event, sf::RenderWindow& window, int& gameState);
    void update();
    void render(sf::RenderWindow& window);
    int getFpsLimit() const;

private:
    sf::Font font;
    sf::Text title;
    std::vector<sf::Text> menuOptions;
    int selectedOption;
    int fpsLimit;

    std::vector<sf::CircleShape> fogParticles;
    std::vector<sf::Vector2f> fogSpeeds;
    void initFogParticles();
};