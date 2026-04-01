#include "../Header/WorldGenerator.hpp"

void WorldGenerator::GenerateChunk(Chunk& chunk)
{
    static PerlinNoise Noise(2026);

    for (int y = 0; y < Chunk::SIZE; ++y)
    {
        for (int x = 0; x < Chunk::SIZE; ++x)
        {
            int wx = chunk.cx * Chunk::SIZE + x;
            int wy = chunk.cy * Chunk::SIZE + y;

            float fx = (float)wx;
            float fy = (float)wy;

            // ===== NHẸ domain warp (giữ bờ biển mượt) =====
            float warp = Noise.noise(fx * 0.0012f, fy * 0.0012f);
            fx += warp * 12.f;
            fy += warp * 12.f;

            // ===== CONTINENT =====
            float continent = Noise.noise(fx * 0.0010f, fy * 0.0010f);
            continent = (continent + 1.f) / 2.f;

            CELL& cell = chunk.Get(x, y);

            // ===== OCEAN & BEACH (rộng, mượt) =====
            if (continent < 0.40f)
            {
                cell.CellType = TTYPE::WATER;
                continue;
            }
            else if (continent < 0.52f) // BEACH RỘNG
            {
                cell.CellType = TTYPE::SAND;
                continue;
            }

            // ===== BIOME NOISE (quyết định sa mạc/cỏ) =====
            float biome = Noise.noise(fx * 0.0018f, fy * 0.0018f);
            biome = (biome + 1.f) / 2.f;

            // ===== TERRAIN =====
            float terrain = 0;
            float amp = 1, freq = 1, maxAmp = 0;

            for (int o = 0; o < 4; ++o)
            {
                terrain += Noise.noise(fx * 0.025f * freq, fy * 0.025f * freq) * amp;
                maxAmp += amp;
                amp *= 0.5f;
                freq *= 2.f;
            }

            terrain /= maxAmp;
            terrain = (terrain + 1.f) / 2.f;

            // ===== ROCK NOISE (vừa phải, không quá to) =====
            float rockNoise = Noise.noise(fx * 0.020f, fy * 0.020f);
            rockNoise = (rockNoise + 1.f) / 2.f;

            // ===== MOUNTAIN (hiếm) =====
            if (terrain > 0.86f && rockNoise > 0.65f)
            {
                cell.CellType = TTYPE::ROCK;
                continue;
            }

            // ===== BIOME quyết định chính =====
            bool isDesert = biome < 0.32f;   // vùng sa mạc rất to, rõ ràng

            if (isDesert)
            {
                // Sa mạc có ít đá
                if (rockNoise > 0.72f)
                    cell.CellType = TTYPE::ROCK;
                else
                    cell.CellType = TTYPE::SAND;
            }
            else
            {
                // Đồng cỏ có đá nhiều hơn
                if (rockNoise > 0.60f)
                    cell.CellType = TTYPE::ROCK;
                else
                    cell.CellType = TTYPE::GRASS;
            }
        }
    }
}