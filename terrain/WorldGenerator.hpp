#pragma once

#include "core/World.hpp"
#include "terrain/PerlineNoise.hpp"

class WorldGenerator
{
public:
    static void GenerateChunk(Chunk& chunk, long long seed);
};