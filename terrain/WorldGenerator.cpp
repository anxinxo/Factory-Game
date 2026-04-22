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

void WorldGenerator::GenerateResource(Chunk& chunk, long long seed)
{
    // ===== FIELD NOISE (quyết định vùng mỏ / rừng) =====
    PerlinNoise forestField(seed + 1000);

    PerlinNoise ironField  (seed + 2000);
    PerlinNoise coalField  (seed + 3000);
    PerlinNoise copperField(seed + 4000);
    PerlinNoise platField  (seed + 5000);

    // ===== CELL NOISE (lỗ trong mỏ) =====
    PerlinNoise ironCell  (seed + 202);
    PerlinNoise coalCell  (seed + 303);
    PerlinNoise copperCell(seed + 404);
    PerlinNoise platCell  (seed + 505);

    // ===== AMOUNT NOISE =====
    PerlinNoise ironRich  (seed + 2202);
    PerlinNoise coalRich  (seed + 2303);
    PerlinNoise copperRich(seed + 2404);
    PerlinNoise platRich  (seed + 2505);

    auto biomeWeight = [](BIOME b)
    {
        switch (b)
        {
            case BIOME::ROCKY_MOUNTAIN: return 1.0f;
            case BIOME::DESERT:         return 0.65f;
            case BIOME::OCEAN:          return 0.45f;
            case BIOME::BEACH:          return 0.30f;
            case BIOME::PLAINS:         return 0.05f;
            default: return 0.0f;
        }
    };

    for (int y = 0; y < Chunk::SIZE; ++y)
    {
        for (int x = 0; x < Chunk::SIZE; ++x)
        {
            CELL& cell = chunk.Get(x, y);
            cell.resource = RESOURCE::NONE;
            cell.amount   = 0;

            int wx = chunk.cx * Chunk::SIZE + x;
            int wy = chunk.cy * Chunk::SIZE + y;

            float fx = (float)wx;
            float fy = (float)wy;

            float w = biomeWeight(cell.Biome);

            // ================= TREE (FOREST FIELD) =================
            if (cell.Biome == BIOME::PLAINS)
            {
                // Macro: quyết định vùng rừng lớn
                float f1 = (forestField.noise(fx*0.006f, fy*0.006f)+1.f)/2.f;

                // Detail: tạo hình rừng tự nhiên, không tròn vo
                float f2 = (forestField.noise(fx*0.035f, fy*0.035f)+1.f)/2.f;

                // Kết hợp 2 lớp
                float forest = f1 * 0.75f + f2 * 0.25f;

                // Ngưỡng thấp hơn rất nhiều
                if (forest > 0.60f)
                {
                    cell.resource = RESOURCE::WOOD;

                    // rừng có độ đậm nhạt
                    float density = (forest - 0.68f) / (1.f - 0.68f);
                    cell.amount = 120.f + density * 260.f;

                    continue;
                }
            }

            // ================= IRON =================
            {
                float field = (ironField.noise(fx*0.006f, fy*0.006f)+1.f)/2.f;
                if (field > 0.965f - 0.45f*w)
                {
                    float n = (ironCell.noise(fx*0.025f, fy*0.025f)+1.f)/2.f;
                    if (n > 0.62f)
                    {
                        float rich = (ironRich.noise(fx*0.08f, fy*0.08f)+1.f)/2.f;
                        cell.resource = RESOURCE::IRON;
                        cell.amount = 200 + rich * 800.f * w;
                        continue;
                    }
                }
            }

            // ================= COAL =================
            {
                float field = (coalField.noise(fx*0.007f, fy*0.007f)+1.f)/2.f;

                float coalWeight;
                switch (cell.Biome)
                {
                    case BIOME::ROCKY_MOUNTAIN: coalWeight = 1.0f;  break;
                    case BIOME::DESERT:         coalWeight = 0.75f; break;
                    case BIOME::PLAINS:         coalWeight = 0.55f; break;
                    case BIOME::OCEAN:          coalWeight = 0.15f; break;
                    case BIOME::BEACH:          coalWeight = 0.10f; break;
                    default: coalWeight = 0.f;
                }

                if (field > 0.955f - 0.42f*coalWeight)
                {
                    float n = (coalCell.noise(fx*0.028f, fy*0.028f)+1.f)/2.f;
                    if (n > 0.60f)
                    {
                        float rich = (coalRich.noise(fx*0.09f, fy*0.09f)+1.f)/2.f;
                        cell.resource = RESOURCE::COAL;
                        cell.amount = 260.f + rich * 520.f * coalWeight;
                        continue;
                    }
                }
            }

            // ================= COPPER =================
            {
                float field = (copperField.noise(fx*0.006f, fy*0.006f)+1.f)/2.f;
                if (field > 0.972f - 0.45f*w)
                {
                    float n = (copperCell.noise(fx*0.026f, fy*0.026f)+1.f)/2.f;
                    if (n > 0.64f)
                    {
                        float rich = (copperRich.noise(fx*0.085f, fy*0.085f)+1.f)/2.f;
                        cell.resource = RESOURCE::COPPER;
                        cell.amount = 180 + rich * 700.f * w;
                        continue;
                    }
                }
            }

            // ================= PLATINUM (rất hiếm) =================
            {
                float field = (platField.noise(fx*0.004f, fy*0.004f)+1.f)/2.f;
                if (field > 0.992f - 0.55f*w)
                {
                    float n = (platCell.noise(fx*0.03f, fy*0.03f)+1.f)/2.f;
                    if (n > 0.70f)
                    {
                        float rich = (platRich.noise(fx*0.1f, fy*0.1f)+1.f)/2.f;
                        cell.resource = RESOURCE::PLATINUM;
                        cell.amount = 400 + rich * 1200.f * w;
                        continue;
                    }
                }
            }
        }
    }
}