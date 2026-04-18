#include "core/World.hpp"

World::World(long long _seed, sf::Vector2u windowSize): seed(_seed) 
{
    view.setSize(windowSize.x, windowSize.y);
    view.setCenter(view.getSize() / 2.f);
}

sf::View& World::GetView()
{
    return view;
}

void World::FixView(sf::RenderWindow& window)
{
    float windowRatio = (float)window.getSize().x / window.getSize().y;
    float viewRatio   = view.getSize().x / view.getSize().y;

    if (windowRatio > viewRatio)
    {
        float newWidth = view.getSize().y * windowRatio;
        view.setSize(newWidth, view.getSize().y);
    }
    else
    {
        float newHeight = view.getSize().x / windowRatio;
        view.setSize(view.getSize().x, newHeight);
    }

    window.setView(view);
}

long long World::Hash(int x, int y) const
{
    return ( (long long)x << 32 ) ^ (long long)y;
}

Chunk& World::GetChunk(int cx, int cy)
{
    long long h = Hash(cx, cy);

    auto it = chunks.find(h);
    if (it == chunks.end())
    {
        auto [iter, _] = chunks.emplace(h, Chunk(cx, cy));

        WorldGenerator::GenerateChunk(iter->second, seed);

        return iter->second;
    }

    return it->second;
}

CELL& World::GetCell(int wx, int wy)
{
    int cx = floor((float)wx / Chunk::SIZE);
    int cy = floor((float)wy / Chunk::SIZE);

    int lx = (wx % Chunk::SIZE + Chunk::SIZE) % Chunk::SIZE;
    int ly = (wy % Chunk::SIZE + Chunk::SIZE) % Chunk::SIZE;

    return GetChunk(cx, cy).Get(lx, ly);
}

bool World::HasChunk(int cx, int cy) const
{
    long long key = Hash(cx, cy);
    return chunks.find(key) != chunks.end();
}

long long World::getSeed() const
{
    return seed;
}