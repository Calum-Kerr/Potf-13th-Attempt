#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <vector>
#include "GameWorld.h"
#include "Player.h"

class Enemy {
public:
    Enemy();
    void update(GameWorld& world, float deltaTime, const Player& player);
    void render(sf::RenderWindow& window);
    void reset();

    bool isDead() const { return health <= 0; }
    void takeDamage(int dmg);

    sf::FloatRect getBounds() const { return sprite.getGlobalBounds(); }
	bool getAndClearAttackFinished() {
		bool val = attackJustFinished;
		attackJustFinished = false;
		return val;
	}

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
    void handleAI(const Player& player);
    void updateAnimation();
    void goHurt();
    void goDeath();
};