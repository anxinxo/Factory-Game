#include "../Header/WorldGenerator.hpp"

    void WorldGenerator::GenerateChunk(Chunk& chunk)
    {
        static PerlinNoise Noise(2026);

        for (int y = 0; y < Chunk::SIZE; ++y)
        {
            for (int x = 0; x < Chunk::SIZE; ++x)
            {
                // ===== World cell coord (QUAN TRỌNG) =====
                int wx = chunk.cx * Chunk::SIZE + x;
                int wy = chunk.cy * Chunk::SIZE + y;

                float fx = wx;
                float fy = wy;

                // ===== Domain warp =====
                float warp = Noise.noise(fx * 0.003f, fy * 0.003f);
                fx += warp * 120.0f;
                fy += warp * 120.0f;

                // ===== Continent =====
                float continent = Noise.noise(fx * 0.004f, fy * 0.004f);
                continent = (continent + 1.0f) / 2.0f;

                // ===== Terrain octave =====
                float terrain = 0;
                float amp = 1, freq = 1, maxAmp = 0;

                for (int o = 0; o < 4; ++o)
                {
                    terrain += Noise.noise(fx * 0.06f * freq, fy * 0.06f * freq) * amp;
                    maxAmp += amp;
                    amp *= 0.5f;
                    freq *= 2.0f;
                }

                terrain /= maxAmp;
                terrain = (terrain + 1.0f) / 2.0f;

                // ===== Detail =====
                float detail = Noise.noise(fx * 0.25f, fy * 0.25f);
                detail = (detail + 1.0f) / 2.0f;

                terrain = terrain * 0.8f + detail * 0.2f;

                // ===== Quyết định tile =====
                CELL& cell = chunk.Get(x, y);

                if (continent < 0.45f)
                {
                    cell.CellType = TTYPE::WATER;
                }
                else
                {
                    if (terrain < 0.38f) cell.CellType = TTYPE::SAND;
                    else if (terrain < 0.72f) cell.CellType = TTYPE::GRASS;
                    else cell.CellType = TTYPE::ROCK;
                }
            }
        }
    }