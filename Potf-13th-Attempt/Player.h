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
    bool isOnFloor(const GameWorld& world) const;

    bool isDead() const { return health <= 0; }
    void takeDamage(int dmg) {
        if (dying) return;
        health -= dmg;
        if (health <= 0) goHurt();
        else goHurt();
    }

    sf::FloatRect getSpriteBounds() const { return sprite.getGlobalBounds(); }

    void reset();

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

    int health;
    bool attacking;
    bool hurting;
    bool dying;
    bool attackJustFinished;

    void loadAnimations();
    void handleInput();
    void updateAnimation();
    void goHurt();
    void goDeath();
};