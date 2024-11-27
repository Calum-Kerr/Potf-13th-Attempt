#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include<SFML/Graphics.hpp>
#include<vector>
#include<string>

// reference: creating pause menus explained in sfml game tutorials (https://www.sfml-dev.org/tutorials/2.5/window-events.php)
class PauseMenu {
private:
    sf::Font font;
    sf::Text title;
    std::vector<sf::Text> menuOptions;
    int selectedOption;

public:
    PauseMenu();
    void handleInput(sf::RenderWindow& window, bool& isPaused, int& gameState);
    void render(sf::RenderWindow& window);
};

#endif