#ifndef MAINMENU_H
#define MAINMENU_H

#include<SFML/Graphics.hpp>
#include<vector>
#include<string>

// reference: creating a class for menu management explained in sfml official tutorials (https://www.sfml-dev.org/tutorials/2.5/graphics-sprite.php)
class MainMenu {
private:
    sf::Font font;
    sf::Text title;
    std::vector<sf::Text> menuOptions;
    int selectedOption;

public:
    MainMenu();
    void handleInput(sf::RenderWindow& window);
    void update();
    void render(sf::RenderWindow& window);
};

#endif