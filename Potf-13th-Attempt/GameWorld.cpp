#include "GameWorld.h"
// reference: tiling a background in sfml explained in sprite documentation (https://www.sfml-dev.org/tutorials/2.5/graphics-sprite.php)

GameWorld::GameWorld() : tileSize(160), gridSize(8, 5) { // 8x5 grid for 1280x720
    if (!tilemapTexture.loadFromFile("160x160 background tilemap.png"))
        throw std::runtime_error("failed to load tilemap texture");

    tileSprite.setTexture(tilemapTexture);
    tileSprite.setScale(1.0f, 1.0f); // scale (no scaling needed for 160x160 tiles)
}

void GameWorld::render(sf::RenderWindow& window) {
    for (int y = 0; y < gridSize.y; ++y) {
        for (int x = 0; x < gridSize.x; ++x) {
            tileSprite.setPosition(x * tileSize, y * tileSize); // position tile
            window.draw(tileSprite);
        }
    }
}