#include "Enemy.h"
#include <stdexcept>
#include <cmath>

Enemy::Enemy()
    : currentState("Idle"), previousState("Idle"), currentFrame(0),
    facingRight(true), jumping(false), health(3),
    attacking(false), hurting(false), dying(false), attackJustFinished(false)
{
    // load the same textures as player
    textures["Idle"].loadFromFile("Player Sword Idle 48x48.png");
    textures["Walk"].loadFromFile("PlayerWalk 48x48.png");
    textures["Run"].loadFromFile("Player_Sword_Run_48x48.png");
    textures["Attack"].loadFromFile("Player Sword atk 64x64.png");
    textures["Hurt"].loadFromFile("Player Hurt 48x48.png");
    textures["Death"].loadFromFile("Player Death 64x64.png");
    textures["Jump"].loadFromFile("player new jump 48x48.png");

    sprite.setTexture(textures["Idle"]);
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 48));
    sprite.setPosition(600, 600); // start somewhere
    sprite.setScale(1.0f, 1.0f);

    loadAnimations();
}

void Enemy::loadAnimations() {
    animations["Idle"] = {
        sf::IntRect(0, 0, 48, 48),
        sf::IntRect(48, 0, 48, 48),
        sf::IntRect(96, 0, 48, 48),
        sf::IntRect(144, 0, 48, 48),
        sf::IntRect(192, 0, 48, 48),
        sf::IntRect(240, 0, 48, 48),
        sf::IntRect(288, 0, 48, 48),
        sf::IntRect(336, 0, 48, 48),
        sf::IntRect(384, 0, 48, 48),
        sf::IntRect(432, 0, 48, 48),
        sf::IntRect(480, 0, 48, 48),
    };
    animations["Walk"] = {
        sf::IntRect(0,0,48,48),
        sf::IntRect(48,0,48,48),
        sf::IntRect(96,0,48,48),
        sf::IntRect(144,0,48,48),
        sf::IntRect(192,0,48,48),
        sf::IntRect(240,0,48,48),
        sf::IntRect(288,0,48,48),
        sf::IntRect(336,0,48,48),
    };
    animations["Run"] = {
        sf::IntRect(0,0,48,48),
        sf::IntRect(48,0,48,48),
        sf::IntRect(96,0,48,48),
        sf::IntRect(144,0,48,48),
        sf::IntRect(192,0,48,48),
        sf::IntRect(240,0,48,48),
        sf::IntRect(288,0,48,48),
        sf::IntRect(336,0,48,48),
    };
    animations["Jump"] = {
        sf::IntRect(0,0,48,48),
        sf::IntRect(48,0,48,48),
        sf::IntRect(96,0,48,48),
        sf::IntRect(144,0,48,48),
        sf::IntRect(192,0,48,48),
        sf::IntRect(240,0,48,48)
    };
    animations["Attack"] = {
        sf::IntRect(0,0,64,64),
        sf::IntRect(64,0,64,64),
        sf::IntRect(128,0,64,64),
        sf::IntRect(192,0,64,64),
        sf::IntRect(256,0,64,64),
        sf::IntRect(320,0,64,64)
    };
    animations["Hurt"] = {
        sf::IntRect(0,0,48,48),
        sf::IntRect(48,0,48,48),
        sf::IntRect(96,0,48,48)
    };
    animations["Death"] = {
        sf::IntRect(0,0,64,64),
        sf::IntRect(64,0,64,64),
        sf::IntRect(128,0,64,64),
        sf::IntRect(192,0,64,64),
        sf::IntRect(256,0,64,64)
    };
}

void Enemy::handleAI(const Player& player) {
    if (dying) return;
    velocity.x = 0;
    previousState = currentState;

    // get player position and enemy position
    float playerX = player.getSpriteBounds().left + player.getSpriteBounds().width * 0.5f;
    float enemyX = getBounds().left + getBounds().width * 0.5f;
    float dist = std::fabs(playerX - enemyX);

    // if player is to the left, move left; if right, move right
    if (playerX < enemyX - 50) {
        velocity.x = -50;
        facingRight = false;
    }
    else if (playerX > enemyX + 50) {
        velocity.x = 50;
        facingRight = true;
    }
    else {
        // close enough horizontally
        // try to attack if not attacking or hurting or dying
        if (!attacking && !hurting && !dying && dist < 88) {
            currentState = "Attack";
            currentFrame = 0;
            sprite.setTexture(textures["Attack"]);
            sprite.setTextureRect(animations["Attack"][0]);
            animationClock.restart();
            attacking = true;
        }
    }

    // if we're moving but not attacking, set run or walk
    if (!attacking && !hurting && !dying) {
        if (velocity.x != 0) {
            currentState = "Run";
        }
        else {
            currentState = "Idle";
        }
    }

    if (currentState != previousState && currentState != "Attack" && !hurting && !dying) {
        sprite.setTexture(textures[currentState]);
        currentFrame = 0;
        sprite.setTextureRect(animations[currentState][0]);
        animationClock.restart();
    }
}

void Enemy::updateAnimation() {
    if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
        currentFrame = (currentFrame + 1) % animations[currentState].size();
        sprite.setTextureRect(animations[currentState][currentFrame]);
        animationClock.restart();

        // attack finished?
        if (currentState == "Attack" && currentFrame == (int)animations["Attack"].size() - 1) {
            currentState = "Idle";
            sprite.setTexture(textures["Idle"]);
            currentFrame = 0;
            sprite.setTextureRect(animations["Idle"][0]);
            attacking = false;
            attackJustFinished = true;
        }

        // hurt finished?
        if (currentState == "Hurt" && currentFrame == (int)animations["Hurt"].size() - 1) {
            if (health <= 0) {
                goDeath(); // trigger death when hurt animation completes if health is 0
            }
            else {
                currentState = "Idle";
                sprite.setTexture(textures["Idle"]);
                currentFrame = 0;
                sprite.setTextureRect(animations["Idle"][0]);
                hurting = false;
            }
        }

        // death animation
        if (currentState == "Death" && currentFrame == (int)animations["Death"].size() - 1) {
            currentFrame = animations["Death"].size(); 
            sprite.setTextureRect(animations["Death"][currentFrame]);
        }
    }
}

void Enemy::update(GameWorld& world, float deltaTime, const Player& player) {
    handleAI(player);
    updateAnimation();

    if (!dying) {
        // simple gravity
        if (velocity.y < 1000) {
            velocity.y += 98.0f * deltaTime;
        }

        sprite.move(velocity.x * deltaTime, velocity.y * deltaTime);

        if (world.isOnFloor(sprite)) {
            velocity.y = 0;
            if (jumping) jumping = false;

            sf::FloatRect enemyBounds = sprite.getGlobalBounds();
            int floorY = 720 - 32;
            if (sprite.getPosition().y > floorY - enemyBounds.height) {
                sprite.setPosition(sprite.getPosition().x, floorY - enemyBounds.height);
                velocity.y = 0;
                jumping = false;
            }
        }
    }

    sprite.setScale(facingRight ? 1.0f : -1.0f, 1.0f);
}

void Enemy::render(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Enemy::reset() {
    health = 2; 
    currentState = "Idle";
    previousState = "Idle";
    currentFrame = 0;
    facingRight = true;
    jumping = false;
    attacking = false;
    hurting = false;
    dying = false;
    attackJustFinished = false;
    velocity = sf::Vector2f(0, 0);

    sprite.setTexture(textures["Idle"]);
    sprite.setTextureRect(animations["Idle"][0]);
    sprite.setPosition(600, 600);
}

void Enemy::takeDamage(int dmg) {
    if (dying) return;

    health -= dmg;

    if (health <= 0) {
        goDeath(); // directly go to death if health reaches 0
    }
    else {
        goHurt(); // show hurt animation if still alive
    }
}

void Enemy::goHurt() {
    if (!dying) {
        currentState = "Hurt";
        sprite.setTexture(textures["Hurt"]);
        currentFrame = 0;
        sprite.setTextureRect(animations["Hurt"][0]);
        animationClock.restart();
        hurting = true;
        attacking = false;
    }
}

void Enemy::goDeath() {
    currentState = "Death";
    sprite.setTexture(textures["Death"]);
    currentFrame = 0;
    sprite.setTextureRect(animations["Death"][0]);
    animationClock.restart();
    dying = true;
    hurting = false;
    attacking = false;
}