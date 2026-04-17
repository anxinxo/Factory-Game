#pragma once

#include <unordered_map>
#include <cmath>
#include "../terrain/Chunk.hpp"
#include "../terrain/WorldGenerator.hpp"

class World
{
private:
    sf::View view;
public:

    World(long long _seed, sf::Vector2u windowSize);
    
    void FixView(sf::RenderWindow& window);
    sf::View& GetView();

    Chunk& GetChunk(int cx, int cy);
    CELL& GetCell(int wx, int wy);
    bool HasChunk(int cx, int cy) const;

    long long getSeed() const;
private:
    long long seed;
    std::unordered_map<long long, Chunk> chunks;

    long long Hash(int x, int y) const;
};