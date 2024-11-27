#ifndef MAINMENU_H
#define MAINMENU_H

#include<SFML/Graphics.hpp>
#include<vector>
#include<string>

// reference: creating particle effects in sfml explained in sfml vertex array tutorial (https://www.sfml-dev.org/tutorials/2.5/graphics-vertex-array.php)
class MainMenu {
private:
    sf::Font font;
    sf::Text title;
    std::vector<sf::Text> menuOptions;
    int selectedOption;

    // fog particle system
    std::vector<sf::CircleShape> fogParticles;

    void initFogParticles();

public:
    MainMenu();
    void handleInput(sf::RenderWindow& window, int& gameState);
    void update();
    void render(sf::RenderWindow& window);
};

#endif