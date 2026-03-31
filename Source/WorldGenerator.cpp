#include "../Header/WorldGenerator.hpp"

void WorldGenerator::Generate(Map &MAP)
{
    PerlinNoise Noise(2026);

    sf::Vector2i RC = MAP.GetRC();
    int Size = MAP.Get_Cell_Size();

    for(int i = 0; i < RC.y; ++i)
    {
        for(int j = 0; j < RC.x; ++j)
        {
            // ===== World space coordinate =====
            float x = j * Size;
            float y = i * Size;

            // ===== Domain warp (làm bờ cong tự nhiên) =====
            float warp = Noise.noise(x * 0.003f, y * 0.003f);
            x += warp * 120.0f;
            y += warp * 120.0f;

            // ===== CONTINENT NOISE (rất low freq) =====
            float continent = Noise.noise(x * 0.004f, y * 0.004f);
            continent = (continent + 1.0f) / 2.0f;

            // ===== TERRAIN NOISE (octave mid freq) =====
            float terrain = 0;
            float amp = 1, freq = 1, maxAmp = 0;

            for(int o = 0; o < 4; ++o)
            {
                terrain += Noise.noise(x * 0.06f * freq, y * 0.06f * freq) * amp;
                maxAmp += amp;
                amp *= 0.5f;
                freq *= 2.0f;
            }

            terrain /= maxAmp;
            terrain = (terrain + 1.0f) / 2.0f;

            // ===== DETAIL NOISE (high freq, phá răng cưa) =====
            float detail = Noise.noise(x * 0.25f, y * 0.25f);
            detail = (detail + 1.0f) / 2.0f;

            terrain = terrain * 0.8f + detail * 0.2f;

            // ===== Island falloff (tròn) =====
            float nx = (float)j / RC.x * 2 - 1;
            float ny = (float)i / RC.y * 2 - 1;
            float d = sqrt(nx * nx + ny * ny);
            float falloff = pow(d, 2) * 0.8f;
            continent -= falloff;

            // ===== Quyết định tile =====
            if(continent < 0.45f)
            {
                MAP.setType(i, j, TTYPE::WATER);
            }
            else
            {
                if(terrain < 0.38f)      MAP.setType(i, j, TTYPE::SAND);
                else if(terrain < 0.72f) MAP.setType(i, j, TTYPE::GRASS);
                else                     MAP.setType(i, j, TTYPE::ROCK);
            }
        }
    }
}