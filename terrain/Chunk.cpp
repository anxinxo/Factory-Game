#include <terrain/Chunk.hpp>

Chunk::Chunk(int _cx, int _cy): cx(_cx), cy(_cy) {}

CELL &Chunk::Get(int x, int y)
{
    return cells[x][y];
}

std::string Chunk::GetCellType(int x, int y)
{   
    TTYPE t = cells[x][y].CellType;

    if(t == TTYPE::NONE) return "Unknow";
    if(t == TTYPE::GRASS) return "Grass";
    if(t == TTYPE::ROCK) return "Rock";
    if(t == TTYPE::SAND) return "Sand";
    if(t == TTYPE::WATER) return "Water";

    return "Unknow";
}

std::string Chunk::GetCellBiome(int x, int y)
{
    BIOME t = cells[x][y].Biome;

    if(t == BIOME::NONE) return "Unknow";
    if(t == BIOME::PLAINS) return "Plain";
    if(t == BIOME::BEACH) return "Beach";
    if(t == BIOME::ROCKY_MOUNTAIN) return "Rocky mountain";
    if(t == BIOME::OCEAN) return "Ocean";
    if(t == BIOME::DESERT) return "Desert";

    return "Unknow";
}