#ifndef MAINMENU_H
#define MAINMENU_H

#include<SFML/Graphics.hpp>
#include<vector>
#include<string>

class MainMenu {
private:
    sf::Font font;
    sf::Text title;
    std::vector<sf::Text> menuOptions;
    int selectedOption;
    int fpsLimit; // selected FPS limit

    std::vector<sf::CircleShape> fogParticles;
    std::vector<sf::Vector2f> fogSpeeds; // stores speed for each particle

    void initFogParticles();

public:
    MainMenu();
    void handleInput(sf::RenderWindow& window, int& gameState);
    void update();
    void render(sf::RenderWindow& window);
    int getFpsLimit() const; // getter for FPS limit
};

#endif