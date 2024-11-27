#include "GameWorld.h"
// reference: scaling and tiling textures in sfml explained in sprite documentation (https://www.sfml-dev.org/tutorials/2.5/graphics-sprite.php)

GameWorld::GameWorld() : tileSize(48), gridSize(27, 15) { // 27x15 grid for 1280x720 at 48x48 tiles
    if (!tilemapTexture.loadFromFile("160x160 background tilemap.png"))
        throw std::runtime_error("failed to load tilemap texture");

    tileSprite.setTexture(tilemapTexture);
    tileSprite.setScale(48.f / 160.f, 48.f / 160.f); // scale to 48x48 tiles
}

void GameWorld::render(sf::RenderWindow& window) {
    for (int y = 0; y < gridSize.y; ++y) {
        for (int x = 0; x < gridSize.x; ++x) {
            tileSprite.setPosition(x * tileSize, y * tileSize); // position tile
            window.draw(tileSprite);
        }
    }
}