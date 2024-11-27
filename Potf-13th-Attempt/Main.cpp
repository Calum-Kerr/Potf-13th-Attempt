#include<SFML/Graphics.hpp>
// reference: official sfml tutorial for window creation (https://www.sfml-dev.org/tutorials/2.5/start-linux.php)
// reference: text rendering in sfml (https://www.sfml-dev.org/tutorials/2.5/graphics-text.php)
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
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)window.close();
        }
        window.clear();
        window.draw(title); // draw title text
        window.display();
    }
    return 0;
}