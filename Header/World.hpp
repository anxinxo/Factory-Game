#pragma once

#include <unordered_map>
#include <cmath>
#include "../Header/Chunk.hpp"
#include "../Header/WorldGenerator.hpp"

class World
{
public:
    Chunk& GetChunk(int cx, int cy);
    CELL& GetCell(int wx, int wy);
private:
    std::unordered_map<long long, Chunk> chunks;

    long long Hash(int x, int y) const;
};