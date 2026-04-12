#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

class MouseWorld
{
public:
    void Update(const sf::RenderWindow& window, const sf::View& view, int TILE_SIZE, int CHUNK_SIZE);

    sf::Vector2f getWorldPos() const;
    sf::Vector2i getChunkPos() const;
    sf::Vector2i getTilePos() const;

private:
    sf::Vector2f WorldPos;
    sf::Vector2i ChunkPos;
    sf::Vector2i TilePos;
};