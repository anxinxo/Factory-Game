#include "terrain/WorldGenerator.hpp"

void WorldGenerator::GenerateChunk(Chunk& chunk, long long seed)
{
    static PerlinNoise Noise(seed);

    const float seaLevel = 0.44f;
    const float beachLevel = 0.48f;
    const float plateauLevel = 0.85f;

    for (int y = 0; y < Chunk::SIZE; ++y)
    {
        for (int x = 0; x < Chunk::SIZE; ++x)
        {
            int wx = chunk.cx * Chunk::SIZE + x;
            int wy = chunk.cy * Chunk::SIZE + y;

            float fx = (float)wx;
            float fy = (float)wy;

            CELL& cell = chunk.Get(x, y);

            // ===== HEIGHT =====
            float h =
                Noise.noise(fx * 0.002f, fy * 0.002f) * 0.55f +
                Noise.noise(fx * 0.010f, fy * 0.010f) * 0.25f +
                Noise.noise(fx * 0.050f, fy * 0.050f) * 0.15f +
                Noise.noise(fx * 0.120f, fy * 0.120f) * 0.05f;

            h = (h + 1.f) / 2.f;

            // ===== TEMPERATURE =====
            float temp =
                Noise.noise(fx * 0.003f, fy * 0.003f) * 0.6f +
                Noise.noise(fx * 0.020f, fy * 0.020f) * 0.3f +
                Noise.noise(fx * 0.080f, fy * 0.080f) * 0.1f;

            temp = (temp + 1.f) / 2.f;

            // ===== ROCK =====
            float rockMacro = (Noise.noise(fx * 0.015f, fy * 0.015f) + 1.f) / 2.f;
            float rockMicro = (Noise.noise(fx * 0.09f,  fy * 0.09f)  + 1.f) / 2.f;
            float rock = rockMacro * 0.65f + rockMicro * 0.35f;

            cell.height = h;
            cell.temp = temp;
            cell.rock_density = rock;

            // ===== SEA & BEACH =====
            if (h < seaLevel)
            {
                cell.CellType = TTYPE::WATER;
                continue;
            }
            if (h < beachLevel)
            {
                cell.CellType = TTYPE::SAND;
                continue;
            }

            float rockThreshold = 0.78f;

            if (h > plateauLevel) rockThreshold -= 0.18f;
            if (temp > 0.68f)     rockThreshold += 0.06f;
            if (temp < 0.32f)     rockThreshold += 0.02f;
            if (rockMacro > 0.60f) rockThreshold -= 0.10f;

            // ===== PLATEAU =====
            if (h > plateauLevel)
            {
                cell.CellType = (rock > 0.75f) ? TTYPE::ROCK : TTYPE::GRASS;
                continue;
            }

            if (rock > rockThreshold)
            {
                cell.CellType = TTYPE::ROCK;
                continue;
            }

            // ===== BIOME theo nhiệt độ =====
            cell.CellType = (temp > 0.68f) ? TTYPE::SAND : TTYPE::GRASS;
        }
    }
}