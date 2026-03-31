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
            std::vector<CELL> d(COL, CELL(false, TTYPE::NONE));
            Terrain.emplace_back(d);
        }
    }

    bool Map::inBound(int r, int c) const
    {   
        return r >= 0 && c >= 0 && r < ROW && c < COL;
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
        if(!inBound(r, c)) return false;

        return Terrain[r][c].occupied;
    }

    TTYPE Map::getType(int r, int c) const
    {   
        if(!inBound(r, c)) return TTYPE::NONE;

        return Terrain[r][c].CellType;
    }

    void Map::setType(int r, int c, TTYPE TCELL)
    {   
        if(!inBound(r, c)) return;

        Terrain[r][c].CellType = TCELL;
    }