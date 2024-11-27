#ifndef MAINMENU_H
#define MAINMENU_H

#include<SFML/Graphics.hpp>
#include<vector>
#include<string>

// reference: creating particle effects with varying speeds explained in sfml tutorials (https://www.sfml-dev.org/tutorials/2.5/graphics-vertex-array.php)
class MainMenu {
private:
    sf::Font font;
    sf::Text title;
    std::vector<sf::Text> menuOptions;
    int selectedOption;

    // ember particle system
    std::vector<sf::CircleShape> fogParticles;
    std::vector<sf::Vector2f> fogSpeeds; // stores speed for each particle

    void initFogParticles();

public:
    MainMenu();
    void handleInput(sf::RenderWindow& window, int& gameState);
    void update();
    void render(sf::RenderWindow& window);
};

#endif