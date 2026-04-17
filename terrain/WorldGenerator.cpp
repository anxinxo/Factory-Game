#include "../terrain/WorldGenerator.hpp"

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

            // ===== HEIGHT (multi-frequency) =====
            float h =
                Noise.noise(fx * 0.002f, fy * 0.002f) * 0.55f + // shape khi zoom xa
                Noise.noise(fx * 0.010f, fy * 0.010f) * 0.25f + // vùng lớn
                Noise.noise(fx * 0.050f, fy * 0.050f) * 0.15f + // địa hình
                Noise.noise(fx * 0.120f, fy * 0.120f) * 0.05f;  // chi tiết

            h = (h + 1.f) / 2.f;

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

            // ===== TEMPERATURE (multi-frequency) =====
            float temp =
                Noise.noise(fx * 0.003f, fy * 0.003f) * 0.6f +
                Noise.noise(fx * 0.020f, fy * 0.020f) * 0.3f +
                Noise.noise(fx * 0.080f, fy * 0.080f) * 0.1f;

            temp = (temp + 1.f) / 2.f;

            // ===== ROCK DETAIL =====

            float rockMacro = Noise.noise(fx * 0.015f, fy * 0.015f); // vùng đá to
            float rockMicro = Noise.noise(fx * 0.09f,  fy * 0.09f);  // chi tiết

            rockMacro = (rockMacro + 1.f) / 2.f;
            rockMicro = (rockMicro + 1.f) / 2.f;

            float rock = rockMacro * 0.65f + rockMicro * 0.35f;

            float rockThreshold = 0.78f; // mặc định rất khó có đá

            // cao nguyên → nhiều đá
            if (h > plateauLevel)
                rockThreshold -= 0.18f;

            // sa mạc → cực ít đá
            if (temp > 0.68f)
                rockThreshold += 0.06f;

            // rừng → ít đá
            if (temp < 0.32f)
                rockThreshold += 0.02f;

            // nếu đang nằm trong bãi đá macro → dễ ra đá hơn
            if (rockMacro > 0.60f)
                rockThreshold -= 0.10f;

            // ===== PLATEAU (cao, nhiều đá, khô) =====
            if (h > plateauLevel)
            {
                if (rock > 0.75f)
                    cell.CellType = TTYPE::ROCK;
                else
                    cell.CellType = TTYPE::GRASS;
                continue;
            }

            if (rock > rockThreshold)
            {
                cell.CellType = TTYPE::ROCK;
                continue;
            }

            // ===== PLATEAU =====
            if (h > plateauLevel)
            {
                cell.CellType = TTYPE::GRASS;
                continue;
            }

            // ===== BIOME theo nhiệt độ =====
            if (temp > 0.68f)
            {
                cell.CellType = TTYPE::SAND;
            }
            else
            {
                cell.CellType = TTYPE::GRASS;
            }
        }
    }
}