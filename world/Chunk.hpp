#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <worldobjects/WorldObject.hpp>
#include <world/CellView.hpp>
#include <world/WorldType.hpp>

struct CELL
{
    worldobjects* placedObject;

    TTYPE CellType;
    BIOME Biome;
    uint8_t energy;

    float height;
    float temp;
    float rock_density;

    RESOURCE resource;
    float amount;
    
    CELL()
    : placedObject(nullptr),
      CellType(TTYPE::NONE),
      Biome(BIOME::NONE),
      energy(0.f),
      height(0.f),
      temp(0.f),
      rock_density(0.f),
      resource(RESOURCE::NONE),
      amount(0.f) 
    {}
};

class Chunk
{
public:
    static const int SIZE = 32;

    Chunk(int _cx, int _cy);

    CELL& Get(int x, int y);

    CellView MakeView(int x, int y) const;

    std::string GetCellType(int x, int y);
    std::string GetCellBiome(int x, int y);

    int cx, cy;
private:
    CELL cells[SIZE][SIZE];
};
