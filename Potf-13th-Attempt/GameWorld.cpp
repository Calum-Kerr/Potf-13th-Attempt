#include "GameWorld.h"
#include <stdexcept>

// constructor initializes game world and loads textures
GameWorld::GameWorld() :tileSize(32), gridSize(40, 2) {
    if (!backgroundTexture.loadFromFile("160x160 background tilemap.png"))
        throw std::runtime_error("failed to load background texture");

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(1280.f / 160.f, 720.f / 160.f);

    if (!tilemapTexture.loadFromFile("Basic Tilemap.png"))
        throw std::runtime_error("failed to load tilemap texture");

    tileSprite.setTexture(tilemapTexture);
    initTileRects();
}

// this function initializes the tile rectangles for the game world
void GameWorld::initTileRects() {
    tileRects.push_back(sf::IntRect(32, 64, 64, 32));
}

// this function updates the game world (currently empty but can be expanded)
void GameWorld::update(float deltaTime) {
    // update world as needed
}

// this function renders the game world on the window
void GameWorld::render(sf::RenderWindow& window) {
    for (int y = 0; y < 22; ++y) {
        for (int x = 0; x < 40; ++x) {
            backgroundSprite.setPosition(x * 160, y * 160);
            window.draw(backgroundSprite);
        }
    }

    int floorY = 720 - tileSize;
    for (int x = 0; x < gridSize.x; ++x) {
        tileSprite.setTextureRect(tileRects[0]);
        tileSprite.setPosition(x * tileSize, floorY);
        window.draw(tileSprite);
    }
}

// this function checks if the player is on the floor
bool GameWorld::isOnFloor(const sf::Sprite& playerSprite) {
    sf::FloatRect playerBounds = playerSprite.getGlobalBounds();
    int floorY = 720 - 32;
    return playerBounds.top + playerBounds.height >= floorY;
}     
