#pragma once

#include <unordered_map>
#include <cmath>
#include "../Header/Chunk.hpp"
#include "../Header/WorldGenerator.hpp"

class World
{
public:

    World(long long _seed); 

    Chunk& GetChunk(int cx, int cy);
    CELL& GetCell(int wx, int wy);
    bool HasChunk(int cx, int cy) const;

    long long getSeed() const;
private:
    long long seed;
    std::unordered_map<long long, Chunk> chunks;

    long long Hash(int x, int y) const;
};