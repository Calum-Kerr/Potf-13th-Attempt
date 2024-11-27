#include "GameWorld.h"
// reference: layering background and floor in sfml explained in sfml sprite documentation (https://www.sfml-dev.org/tutorials/2.5/graphics-sprite.php)

GameWorld::GameWorld() : tileSize(32), gridSize(40, 2) { // 40 tiles wide, 2 tiles high for a floor
    // load background texture
    if (!backgroundTexture.loadFromFile("160x160 background tilemap.png"))
        throw std::runtime_error("failed to load background texture");

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(1280.f / 160.f, 720.f / 160.f); // scale background to fill screen

    // load floor tilemap texture
    if (!tilemapTexture.loadFromFile("Basic Tilemap.png"))
        throw std::runtime_error("failed to load tilemap texture");

    tileSprite.setTexture(tilemapTexture);
    initTileRects(); // initialize sub-rectangles for individual tiles
}

void GameWorld::initTileRects() {
    // Add specific floor tile sub-rectangle
    tileRects.push_back(sf::IntRect(0, 32, 32, 32)); // Floor tile (adjust coordinates if needed)
}

void GameWorld::render(sf::RenderWindow& window) {
    // Draw the repeating background
    for (int y = 0; y < 22; ++y) { // Enough tiles to cover the vertical space
        for (int x = 0; x < 40; ++x) { // Enough tiles to cover the horizontal space
            backgroundSprite.setPosition(x * 160, y * 160); // Position each tile
            window.draw(backgroundSprite);
        }
    }

    // Render floor tiles
    int floorY = 720 - tileSize; // Position the floor at the bottom
    for (int x = 0; x < gridSize.x; ++x) {
        tileSprite.setTextureRect(tileRects[0]); // Use the floor tile
        tileSprite.setPosition(x * tileSize, floorY); // Position the tile
        window.draw(tileSprite);
    }
}