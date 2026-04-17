#include "../input/MouseWorld.hpp"

void MouseWorld::Update(const sf::RenderWindow& window, const sf::View& view, int TILE_SIZE, int CHUNK_SIZE)
{
    sf::Vector2i pixel = sf::Mouse::getPosition(window);
    WorldPos = window.mapPixelToCoords(pixel, view);

    TilePos.x = (int)floor(WorldPos.x / TILE_SIZE);
    TilePos.y = (int)floor(WorldPos.y / TILE_SIZE);

    ChunkPos.x = (int)floor(TilePos.x / CHUNK_SIZE);
    ChunkPos.y = (int)floor(TilePos.y / CHUNK_SIZE);
}

sf::Vector2f MouseWorld::getWorldPos() const
{
    return WorldPos;
}

sf::Vector2i MouseWorld::getChunkPos() const
{
    return ChunkPos;
}

sf::Vector2i MouseWorld::getTilePos() const
{
    return TilePos;
}