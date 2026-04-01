#include "../Header/World.hpp"

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

            WorldGenerator::GenerateChunk(iter->second);

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