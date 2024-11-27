#include<SFML/Graphics.hpp>
// reference: official sfml tutorial for window creation (https://www.sfml-dev.org/tutorials/2.5/start-linux.php)
// reference: text rendering in sfml (https://www.sfml-dev.org/tutorials/2.5/graphics-text.php)
// reference: menu navigation logic adapted from sfml forums (https://en.sfml-dev.org/forums/index.php?topic=21218.0)
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Path of the Foresaken");
    sf::Font font;
    if (!font.loadFromFile("CloisterBlack.ttf"))return -1; // load font

    sf::Text title;
    title.setFont(font);
    title.setString("Path of the Foresaken");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setPosition(200, 100); // position title

    // add menu options
    sf::Text menuOptions[4];
    std::string options[] = { "Start Game", "Continue", "Settings", "Quit" };
    for (int i = 0;i < 4;i++) {
        menuOptions[i].setFont(font);
        menuOptions[i].setString(options[i]);
        menuOptions[i].setCharacterSize(30);
        menuOptions[i].setFillColor(sf::Color::White);
        menuOptions[i].setPosition(250, 200 + (i * 50)); // position each option
    }

    int selectedOption = 0;
    menuOptions[selectedOption].setFillColor(sf::Color::Red); // highlight first option

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    menuOptions[selectedOption].setFillColor(sf::Color::White); // reset previous
                    selectedOption = (selectedOption - 1 + 4) % 4; // move up
                    menuOptions[selectedOption].setFillColor(sf::Color::Red); // highlight new
                }
                if (event.key.code == sf::Keyboard::Down) {
                    menuOptions[selectedOption].setFillColor(sf::Color::White); // reset previous
                    selectedOption = (selectedOption + 1) % 4; // move down
                    menuOptions[selectedOption].setFillColor(sf::Color::Red); // highlight new
                }
            }
        }

        window.clear();
        window.draw(title); // draw title text
        for (int i = 0;i < 4;i++)window.draw(menuOptions[i]); // draw menu options
        window.display();
    }
    return 0;
}