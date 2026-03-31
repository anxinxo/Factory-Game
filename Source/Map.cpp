#include "../Header/Map.hpp"

    Map::Map(int _W, int _H, int _CellSize)
    : WIDTH(_W), 
    HEIGHT(_H), 
    Cell_Size(_CellSize)
    {
        ROW = HEIGHT / Cell_Size;
        COL = WIDTH / Cell_Size;

        for(int i = 0; i < ROW; ++i)
        {
            std::vector<CELL> d(COL, CELL(false, TTYPE::GRASS));
            Terrain.emplace_back(d);
        }
    }

    sf::Vector2i Map::GetRC() const
    {
        return sf::Vector2i(ROW, COL);
    }

    int Map::Get_Cell_Size() const
    {
        return Cell_Size;
    }

    bool Map::isOccupied(int r, int c) const
    {   
        return Terrain[r][c].occupied;
    }

    TTYPE Map::getType(int r, int c) const
    {
        return Terrain[r][c].CellType;
    }
