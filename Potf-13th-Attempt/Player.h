#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class GameWorld; // forward declaration to avoid circular includes

class Player {
public:
    Player();
    void update(GameWorld& world); // pass game world for collision
    void render(sf::RenderWindow& window); // renders the player

private:
    sf::Sprite sprite;
    sf::Vector2f velocity;
    bool facingRight;
    bool jumping;
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, std::vector<sf::IntRect>> animations;
    int currentFrame;
    std::string currentState;
    std::string previousState;
    sf::Clock animationClock;

    void handleInput(); // handles user input
    void updateAnimation(); // updates animation frames
    void loadAnimations(); // loads animation frames

};

#endif