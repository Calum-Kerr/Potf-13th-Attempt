#include "Player.h"
#include "GameWorld.h"

// reference: handling sprite animations in sfml explained in sprite documentation (https://www.sfml-dev.org/tutorials/2.5/graphics-sprite.php)

Player::Player() : currentState("Idle"), previousState("Idle"), currentFrame(0), facingRight(true), jumping(false) {
    textures["Idle"].loadFromFile("Player Sword Idle 48x48.png");
    textures["Walk"].loadFromFile("PlayerWalk 48x48.png");
    textures["Run"].loadFromFile("Player_Sword_Run_48x48.png");
    textures["Attack"].loadFromFile("Player Sword atk 64x64.png");
    textures["Hurt"].loadFromFile("Player Hurt 48x48.png");
    textures["Death"].loadFromFile("Player Death 64x64.png");
    textures["Jump"].loadFromFile("player new jump 48x48.png");

    // Set the initial texture (Idle)
    sprite.setTexture(textures["Idle"]);
    sprite.setScale(1.0f, 1.0f); // Default scale
    sprite.setTextureRect(sf::IntRect(0, 0, 48, 48)); // Set to the first frame of Idle

    // Load animations
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
        sf::IntRect(0, 0, 48, 48),
        sf::IntRect(48, 0, 48, 48),
        sf::IntRect(96, 0, 48, 48),
        sf::IntRect(144, 0, 48, 48),
        sf::IntRect(192, 0, 48, 48),
        sf::IntRect(240, 0, 48, 48),
		sf::IntRect(288, 0, 48, 48),
		sf::IntRect(336, 0, 48, 48), 
    };
    animations["Run"] = {
        sf::IntRect(0, 0, 48, 48),
        sf::IntRect(48, 0, 48, 48),
        sf::IntRect(96, 0, 48, 48),
        sf::IntRect(144, 0, 48, 48),
        sf::IntRect(192, 0, 48, 48),
        sf::IntRect(240, 0, 48, 48),
        sf::IntRect(288, 0, 48, 48),
        sf::IntRect(336, 0, 48, 48),
    };
    animations["Jump"] = {
        sf::IntRect(0, 0, 48, 48),
        sf::IntRect(48, 0, 48, 48),
        sf::IntRect(96, 0, 48, 48),
        sf::IntRect(144, 0, 48, 48),
        sf::IntRect(192, 0, 48, 48),
        sf::IntRect(240, 0, 48, 48)
    };
}

void Player::handleInput() {
    velocity.x = 0; // reset horizontal velocity

    previousState = currentState; // track the previous state

    // horizontal movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        velocity.x = -100; // move left
        facingRight = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        velocity.x = 100; // move right
        facingRight = true;
    }

    // jump
    if (!jumping && (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))) {
        velocity.y = -400; // set upward velocity
        jumping = true;   // player is now jumping
        currentState = "Jump"; // switch to jump state
    }

    // running
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        velocity.x *= 1.5; // increase speed when running
        currentState = "Run";
    }
    else {
        // set state based on movement
        if (!jumping) currentState = (velocity.x != 0) ? "Walk" : "Idle";
    }

    // state transition
    if (currentState != previousState) {
        sprite.setTexture(textures[currentState]); // change to the appropriate texture
        currentFrame = 0; // reset frame
        animationClock.restart();
    }
}

void Player::updateAnimation() {
    if (animationClock.getElapsedTime().asSeconds() > 0.1f) { // Frame delay
        currentFrame = (currentFrame + 1) % animations[currentState].size(); // Loop frames
        sprite.setTextureRect(animations[currentState][currentFrame]);
        animationClock.restart();
    }
}

void Player::update(GameWorld& world) {
    handleInput();
    updateAnimation();

    // apply gravity
    if (velocity.y < 1000) { // terminal velocity limit
        velocity.y += 9.8; // gravity force
    }

    // apply velocity
    sprite.move(velocity.x * 0.016f, velocity.y * 0.016f); // assuming 60 fps

    // check collision with the floor tiles
    if (world.isOnFloor(sprite)) {
        velocity.y = 0; // stop vertical movement
        if (jumping) {
            jumping = false; // reset jumping flag when the player lands
        }

        // snap player to floor level
        sf::FloatRect playerBounds = sprite.getGlobalBounds();
        int floorY = 720 - 32; // assuming the floor is at the bottom (adjust as needed)
        sprite.setPosition(sprite.getPosition().x, floorY - playerBounds.height);
    }

    // flip sprite based on direction
    if (!facingRight) sprite.setScale(-1.0f, 1.0f); // flip sprite if facing left
    else sprite.setScale(1.0f, 1.0f);
}

void Player::render(sf::RenderWindow& window) {
    window.draw(sprite); // draw the player sprite
}