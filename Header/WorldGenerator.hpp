#pragma once

#include "../Header/World.hpp"
#include "../Header/PerlineNoise.hpp"

class WorldGenerator
{
public:
    static void GenerateChunk(Chunk& chunk);
};