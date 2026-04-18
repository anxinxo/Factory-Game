#pragma once

#include <SFML/Graphics.hpp>
#include <string>

enum class TTYPE
{   
    NONE,
    GRASS,
    SAND,
    ROCK,
    WATER
};

enum class BIOME
{   
    NONE,
    PLAINS,
    DESERT,
    BEACH,
    OCEAN
};

struct CELL
{
    bool occupied;
    TTYPE CellType;
    BIOME Biome;
    uint8_t energy;

    float height = 0.f;
    float temp = 0.f;
    float rock_density = 0.f;
    
    CELL()
    : occupied(false),
      CellType(TTYPE::NONE),
      Biome(BIOME::NONE),
      energy(0) 
    {}
};

class Chunk
{
public:
    static const int SIZE = 32;

    Chunk(int _cx, int _cy);

    CELL& Get(int x, int y);

    std::string GetCellType(int x, int y);
    std::string GetCellBiome(int x, int y);

    int cx, cy;
private:
    CELL cells[SIZE][SIZE];
};
