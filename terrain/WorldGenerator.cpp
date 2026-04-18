#include <terrain/WorldGenerator.hpp>

void WorldGenerator::GenerateChunk(Chunk& chunk, long long seed)
{
    PerlinNoise noise(seed);

    const float seaLevel     = 0.44f;
    const float beachLevel   = 0.48f;
    const float plateauLevel = 0.85f;

    for (int y = 0; y < Chunk::SIZE; ++y)
    {
        for (int x = 0; x < Chunk::SIZE; ++x)
        {
            CELL& cell = chunk.Get(x, y);

            // reset nhẹ, không gọi constructor lại
            cell.CellType = TTYPE::NONE;
            cell.Biome    = BIOME::NONE;
            cell.energy   = 0.f;

            int wx = chunk.cx * Chunk::SIZE + x;
            int wy = chunk.cy * Chunk::SIZE + y;

            float fx = (float)wx;
            float fy = (float)wy;

            float h =
                noise.noise(fx * 0.002f, fy * 0.002f) * 0.55f +
                noise.noise(fx * 0.010f, fy * 0.010f) * 0.25f +
                noise.noise(fx * 0.050f, fy * 0.050f) * 0.15f +
                noise.noise(fx * 0.120f, fy * 0.120f) * 0.05f;

            h = (h + 1.f) / 2.f;

            float temp =
                noise.noise(fx * 0.003f, fy * 0.003f) * 0.6f +
                noise.noise(fx * 0.020f, fy * 0.020f) * 0.3f +
                noise.noise(fx * 0.080f, fy * 0.080f) * 0.1f;

            temp = (temp + 1.f) / 2.f;

            float rockMacro = (noise.noise(fx * 0.015f, fy * 0.015f) + 1.f) / 2.f;
            float rockMicro = (noise.noise(fx * 0.09f,  fy * 0.09f)  + 1.f) / 2.f;
            float rock = rockMacro * 0.65f + rockMicro * 0.35f;

            cell.height = h;
            cell.temp   = temp;
            cell.rock_density = rock;

            TTYPE type;

            if (h < seaLevel)          type = TTYPE::WATER;
            else if (h < beachLevel)   type = TTYPE::SAND;
            else
            {
                float rockThreshold = 0.78f;

                if (h > plateauLevel)  rockThreshold -= 0.18f;
                if (temp > 0.68f)      rockThreshold += 0.06f;
                if (temp < 0.32f)      rockThreshold += 0.02f;
                if (rockMacro > 0.60f) rockThreshold -= 0.10f;

                if (h > plateauLevel)
                    type = (rock > 0.75f) ? TTYPE::ROCK : TTYPE::GRASS;
                else if (rock > rockThreshold)
                    type = TTYPE::ROCK;
                else
                    type = (temp > 0.68f) ? TTYPE::SAND : TTYPE::GRASS;
            }

            cell.CellType = type;

            switch (type)
            {
                case TTYPE::WATER:
                    cell.Biome = BIOME::OCEAN;
                    cell.energy = 0.1f;
                    break;

                case TTYPE::SAND:
                    cell.Biome = (temp > 0.65f) ? BIOME::DESERT : BIOME::BEACH;
                    cell.energy = 0.3f;
                    break;

                case TTYPE::GRASS:
                    cell.Biome = BIOME::PLAINS;
                    cell.energy = 0.85f;
                    break;

                case TTYPE::ROCK:
                    cell.Biome = BIOME::ROCKY_MOUNTAIN;
                    cell.energy = 0.2f;
                    break;

                default:
                    break;
            }
        }
    }
}