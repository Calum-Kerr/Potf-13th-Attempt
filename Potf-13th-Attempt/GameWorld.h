#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class GameWorld {
public:
    GameWorld();
    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    bool isOnFloor(const sf::Sprite& playerSprite);

private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Texture tilemapTexture;
    sf::Sprite tileSprite;
    std::vector<sf::IntRect> tileRects;

    int tileSize;
    sf::Vector2i gridSize;

    void initTileRects();
};