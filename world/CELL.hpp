#pragma once

#include <world/WorldType.hpp>
#include <worldobjects/WorldObject.hpp>

struct CELL
{
    WorldObject* placedObject;

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