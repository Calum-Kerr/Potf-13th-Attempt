#include "Player.h"
#include "GameWorld.h"
#include <stdexcept>

// constructor initializes player state and loads textures
Player::Player() :currentState("Idle"), previousState("Idle"), currentFrame(0), facingRight(true), jumping(false) {
    // loading textures for different player states
    textures["Idle"].loadFromFile("Player Sword Idle 48x48.png");
    textures["Walk"].loadFromFile("PlayerWalk 48x48.png");
    textures["Run"].loadFromFile("Player_Sword_Run_48x48.png");
    textures["Attack"].loadFromFile("Player Sword atk 64x64.png");
    textures["Hurt"].loadFromFile("Player Hurt 48x48.png");
    textures["Death"].loadFromFile("Player Death 64x64.png");
    textures["Jump"].loadFromFile("player new jump 48x48.png");

    // setting initial texture and scale for the sprite
    sprite.setTexture(textures["Idle"]);
    sprite.setScale(1.0f, 1.0f);
    sprite.setTextureRect(sf::IntRect(0, 0, 48, 48));

    // loading animations for different states
    loadAnimations();
}

// this function loads the animation frames for each state
void Player::loadAnimations() {
    // idle animation frames
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
    // walk animation frames
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
    // run animation frames
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
    // jump animation frames
    animations["Jump"] = {
        sf::IntRect(0,0,48,48),
        sf::IntRect(48,0,48,48),
        sf::IntRect(96,0,48,48),
        sf::IntRect(144,0,48,48),
        sf::IntRect(192,0,48,48),
        sf::IntRect(240,0,48,48)
    };
}

// this function handles player input and updates the state accordingly
void Player::handleInput() {
    velocity.x = 0;
    previousState = currentState;

    // moving left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        velocity.x = -100; facingRight = false;
    }
    // moving right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        velocity.x = 100; facingRight = true;
    }

    // jumping
    if (!jumping && (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))) {
        velocity.y = -100; jumping = true; currentState = "Jump";
    }

    // running
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        velocity.x *= 1.5; currentState = "Run";
    }
    else { if (!jumping) currentState = (velocity.x != 0) ? "Walk" : "Idle"; }

    // if state changed, update the texture and reset animation
    if (currentState != previousState) {
        sprite.setTexture(textures[currentState]); currentFrame = 0; animationClock.restart();
    }
}

// this function updates the animation frames based on the elapsed time
void Player::updateAnimation() {
    if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
        currentFrame = (currentFrame + 1) % animations[currentState].size(); sprite.setTextureRect(animations[currentState][currentFrame]); animationClock.restart();
    }
}

// this function updates the player's position and state
void Player::update(GameWorld& world, float deltaTime) {
    handleInput();
    updateAnimation();

    // applying gravity
    if (velocity.y < 1000) {
        velocity.y += 98.0f * deltaTime;
    }

    // moving the sprite
    sprite.move(velocity.x * deltaTime, velocity.y * deltaTime);

    // checking if the player is on the floor
    if (world.isOnFloor(sprite)) {
        velocity.y = 0;
        if (jumping)jumping = false;

        // setting the player's position on the floor
        sf::FloatRect playerBounds = sprite.getGlobalBounds();
        int floorY = 720 - 32;
        sprite.setPosition(sprite.getPosition().x, floorY - playerBounds.height);
    }

    // flipping the sprite based on the direction
    sprite.setScale(facingRight ? 1.0f : -1.0f, 1.0f);
}

// this function renders the player sprite on the window
void Player::render(sf::RenderWindow& window) {
    window.draw(sprite);
}