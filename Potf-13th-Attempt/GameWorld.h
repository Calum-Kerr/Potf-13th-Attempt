#pragma once
#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include<SFML/Graphics.hpp>

// reference: handling textures and sprites in sfml explained in sfml sprite documentation (https://www.sfml-dev.org/tutorials/2.5/graphics-sprite.php)
class GameWorld {
private:
    sf::Texture tilemapTexture;
    sf::Sprite tileSprite;
    int tileSize; // size of the tile
    sf::Vector2i gridSize; // size of the grid (in tiles)

public:
    GameWorld();
    void render(sf::RenderWindow& window);
};

#endif