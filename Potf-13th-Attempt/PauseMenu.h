#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include<SFML/Graphics.hpp>
#include<vector>
#include<string>

// reference: creating a background overlay for menus explained in sfml shape tutorial (https://www.sfml-dev.org/tutorials/2.5/graphics-shape.php)
class PauseMenu {
private:
    sf::Font font;
    sf::Text title;
    std::vector<sf::Text> menuOptions;
    int selectedOption;
    sf::RectangleShape background; // background rectangle

public:
    PauseMenu();
    void handleInput(sf::RenderWindow& window, bool& isPaused, int& gameState);
    void render(sf::RenderWindow& window);
};

#endif