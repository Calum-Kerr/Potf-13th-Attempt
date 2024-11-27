#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include<SFML/Graphics.hpp>
#include<vector>

// reference: creating backgrounds and floor tiling explained in sfml tutorials (https://www.sfml-dev.org/tutorials/2.5/graphics-sprite.php)
class GameWorld {
private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Texture tilemapTexture;
    sf::Sprite tileSprite;
    int tileSize; // size of a single tile
    sf::Vector2i gridSize; // size of the grid (in tiles)
    std::vector<sf::IntRect> tileRects; // stores sub-rectangles for individual tiles

    void initTileRects(); // initialize tile sub-rectangles

public:
    GameWorld();
    void render(sf::RenderWindow& window);
};

#endif