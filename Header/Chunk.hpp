#pragma once

#include <SFML/Graphics.hpp>

enum class TTYPE
    {   
        NONE,
        GRASS,
        SAND,
        ROCK,
        WATER
    };

struct CELL
{
    bool occupied;
    TTYPE CellType;
    
    CELL(): occupied(false), CellType(TTYPE::NONE) {}
};

class Chunk
{
public:
    static const int SIZE = 32;

    Chunk(int _cx, int _cy);

    CELL& Get(int x, int y);

    int cx, cy;
private:
    CELL cells[SIZE][SIZE];
};
