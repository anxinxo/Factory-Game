#pragma once
#include <vector>
#include <numeric>
#include <random>
#include <cmath>
#include <algorithm>

class PerlinNoise {
private:
    std::vector<int> p;

    static float fade(float t) {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    static float lerp(float a, float b, float t) {
        return a + t * (b - a);
    }

    static float grad(int hash, float x, float y) {
        switch (hash & 3) {
            case 0: return  x + y;
            case 1: return -x + y;
            case 2: return  x - y;
            case 3: return -x - y;
        }
        return 0;
    }

public:
    PerlinNoise(unsigned int seed);

    float noise(float x, float y) const;
};