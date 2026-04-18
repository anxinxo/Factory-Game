#include "input/HoverSystem.hpp"

void HoverSystem::Update(const MouseWorld& MW, const World& W, int Lx, int Rx, int Uy, int Dy, bool HoverNow)
{
    HoveredTiles.clear();
    if(!HoverNow) return;

    sf::Vector2i BaseTile = MW.getTilePos();

    for(int dx = -Lx; dx <= Rx; ++dx)
    {
        for(int dy = -Uy; dy <= Dy; ++dy)
        {
            int tx = BaseTile.x + dx;
            int ty = BaseTile.y + dy;

            int ChunkX = tx / 32;
            int ChunkY = ty / 32;

            if(W.HasChunk(ChunkX, ChunkY)) HoveredTiles.push_back({tx, ty});
        }
    }
}

const std::vector<sf::Vector2i>& HoverSystem::getHoveredTiles() const 
{
    return HoveredTiles;
}

bool HoverSystem::Isempty() const
{
    return HoveredTiles.empty();
}