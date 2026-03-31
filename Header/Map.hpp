#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

enum class TTYPE
    {
        GRASS,
        SAND,
        ROCK,
        WATER
    };

    struct CELL
    {
        bool occupied;
        TTYPE CellType;

        CELL(bool _oc, TTYPE _T): occupied(_oc), CellType(_T) {}
    };

class Map
{
private:
    int WIDTH, HEIGHT, ROW, COL;
    int Cell_Size;

    std::vector<std::vector<CELL>> Terrain;

public:
    Map(int _W, int _H, int _CellSize);

    sf::Vector2i GetRC() const;
    
    int Get_Cell_Size() const;

    bool isOccupied(int r, int c) const;

    TTYPE getType(int r, int c) const;
};