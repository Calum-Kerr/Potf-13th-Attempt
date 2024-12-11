#include "Player.h"
#include "GameWorld.h"
#include <stdexcept>

Player::Player()
    : currentState("Idle"), previousState("Idle"), currentFrame(0), facingRight(true), jumping(false),
    health(3), attacking(false), hurting(false), dying(false), attackJustFinished(false)
{
    textures["Idle"].loadFromFile("Player Sword Idle 48x48.png");
    textures["Walk"].loadFromFile("PlayerWalk 48x48.png");
    textures["Run"].loadFromFile("Player_Sword_Run_48x48.png");
    textures["Attack"].loadFromFile("Player Sword atk 64x64.png");
    textures["Hurt"].loadFromFile("Player Hurt 48x48.png");
    textures["Death"].loadFromFile("Player Death 64x64.png");
    textures["Jump"].loadFromFile("player new jump 48x48.png");

    sprite.setTexture(textures["Idle"]);
    sprite.setScale(1.0f, 1.0f);
    sprite.setTextureRect(sf::IntRect(0, 0, 48, 48));
    sprite.setPosition(100, 600);

    loadAnimations();
}

void Player::loadAnimations() {
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

void Player::handleInput() {
    if (dying) return;
    velocity.x = 0;
    previousState = currentState;

    if (attacking && currentState == "Attack") {
        return; // finish attack first
    }

    bool moving = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        velocity.x = -100; facingRight = false; moving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        velocity.x = 100; facingRight = true; moving = true;
    }

    if (!jumping && (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))) {
        velocity.y = -100; jumping = true; currentState = "Jump";
        attacking = false; hurting = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        velocity.x *= 1.5;
        if (!jumping && !attacking && !hurting && !dying) currentState = "Run";
    }
    else {
        if (!jumping && !attacking && !hurting && !dying)
            currentState = moving ? "Walk" : "Idle";
    }

    // attack if X pressed
    if (!jumping && !attacking && !hurting && !dying && sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
        currentState = "Attack";
        currentFrame = 0;
        sprite.setTexture(textures["Attack"]);
        sprite.setTextureRect(animations["Attack"][0]);
        animationClock.restart();
        attacking = true;
    }

    if (currentState != previousState && currentState != "Attack" && !hurting && !dying) {
        sprite.setTexture(textures[currentState]);
        currentFrame = 0;
        animationClock.restart();
    }
}

void Player::updateAnimation() {
    if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
        // Force animation progression when dying
        if (currentState == "Death") {
            currentFrame = (currentFrame + 1) % animations["Death"].size();
            sprite.setTextureRect(animations["Death"][currentFrame]);
            animationClock.restart();

            // If we've reached the last frame, stay on the last frame
            if (currentFrame == animations["Death"].size() - 1) {
                // Add a flag to indicate animation is fully complete
                attackJustFinished = true;  // Reusing this as a generic animation complete flag
            }
            return;  // Exit early to ensure only death animation plays
        }

        // Original animation logic for other states
        currentFrame = (currentFrame + 1) % animations[currentState].size();
        sprite.setTextureRect(animations[currentState][currentFrame]);
        animationClock.restart();

        // Attack finished
        if (currentState == "Attack" && currentFrame == (int)animations["Attack"].size() - 1) {
            currentState = "Idle";
            sprite.setTexture(textures["Idle"]);
            currentFrame = 0;
            sprite.setTextureRect(animations["Idle"][0]);
            attacking = false;
            attackJustFinished = true;
        }

        // Hurt finished
        if (currentState == "Hurt" && currentFrame == (int)animations["Hurt"].size() - 1) {
            if (health <= 0) {
                goDeath();
            }
            else {
                currentState = "Idle";
                sprite.setTexture(textures["Idle"]);
                currentFrame = 0;
                sprite.setTextureRect(animations["Idle"][0]);
                hurting = false;
            }
        }
    }
}

void Player::update(GameWorld& world, float deltaTime) {
    if (dying) {
        if (attackJustFinished) {
        }
        return;
    }

    handleInput();
    updateAnimation();

    if (velocity.y < 1000) {
        velocity.y += 98.0f * deltaTime;
    }

    sprite.move(velocity.x * deltaTime, velocity.y * deltaTime);

    if (world.isOnFloor(sprite)) {
        velocity.y = 0;
        if (jumping) jumping = false;

        sf::FloatRect playerBounds = sprite.getGlobalBounds();
        int floorY = 720 - 32;
        if (sprite.getPosition().y + playerBounds.height > floorY) {
            sprite.setPosition(sprite.getPosition().x, floorY - playerBounds.height);
            velocity.y = 0;
            jumping = false;
        }
    }

    sprite.setScale(facingRight ? 1.0f : -1.0f, 1.0f);
}

void Player::goHurt() {
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

void Player::goDeath() {
    currentState = "Death";
    sprite.setTexture(textures["Death"]);
    currentFrame = 0;
    sprite.setTextureRect(animations["Death"][0]);
    animationClock.restart();
    dying = true;
    hurting = false;
    attacking = false;
}

void Player::reset() {
    health = 3;
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
    sprite.setPosition(100, 600);
}
void Player::render(sf::RenderWindow& window) {
	window.draw(sprite);
}