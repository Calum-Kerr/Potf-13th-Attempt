#ifndef MAINMENU_H
#define MAINMENU_H

#include<SFML/Graphics.hpp>
#include<vector>
#include<string>

// reference: handling menu states in sfml explained in official tutorials (https://www.sfml-dev.org/tutorials/2.5/window-events.php)
class MainMenu {
private:
    sf::Font font;
    sf::Text title;
    std::vector<sf::Text> menuOptions;
    int selectedOption;

public:
    MainMenu();
    void handleInput(sf::RenderWindow& window, int& gameState);
    void update();
    void render(sf::RenderWindow& window);
};

#endif
