#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <vector>

class GameWorld;

class Player {
public:
    Player();
    void update(GameWorld& world, float deltaTime);
    void render(sf::RenderWindow& window);

private:
    sf::Sprite sprite;
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, std::vector<sf::IntRect>> animations;
    std::string currentState;
    std::string previousState;
    bool facingRight;
    bool jumping;
    int currentFrame;
    sf::Vector2f velocity;
    sf::Clock animationClock;

    void loadAnimations();
    void handleInput();
    void updateAnimation();
};