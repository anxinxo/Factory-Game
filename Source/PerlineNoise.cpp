#include "../Header/PerlineNoise.hpp"

    PerlinNoise::PerlinNoise(unsigned int seed) {
        p.resize(256);
        std::iota(p.begin(), p.end(), 0);

        std::default_random_engine engine(seed);
        std::shuffle(p.begin(), p.end(), engine);

        p.insert(p.end(), p.begin(), p.end());
    }

    float PerlinNoise::noise(float x, float y) const {
        int xi = (int)std::floor(x) & 255;
        int yi = (int)std::floor(y) & 255;

        float xf = x - std::floor(x);
        float yf = y - std::floor(y);

        float u = fade(xf);
        float v = fade(yf);

        int aa = p[p[xi] + yi];
        int ab = p[p[xi] + yi + 1];
        int ba = p[p[xi + 1] + yi];
        int bb = p[p[xi + 1] + yi + 1];

        float x1 = lerp(grad(aa, xf, yf),
                        grad(ba, xf - 1, yf), u);

        float x2 = lerp(grad(ab, xf, yf - 1),
                        grad(bb, xf - 1, yf - 1), u);

        return lerp(x1, x2, v);
    }