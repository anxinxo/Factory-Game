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
            std::vector<CELL> d(COL, CELL::LAND);
            Terrain.emplace_back(d);
        }
    }

    void Map::Hovering_Cell(sf::Vector2f realPos)
    {   
        int Mcol = realPos.x / Cell_Size;
        int Mrow = realPos.y / Cell_Size;

        if(Mcol < 0 || Mrow < 0 || Mrow >= ROW || Mcol >= COL)
        {
            HoverCell = {-1, -1};
        }
        else
        {
            HoverCell = {Mrow, Mcol};
        }
    }

    void Map::Updating()
    {
        for(int i = 0; i < ROW; ++i)
        {
            for(int j = 0; j < COL; ++j)
            {
            }
        }
    }

    void Map::drawby(sf::RenderWindow& window)
    {   
        sf::RectangleShape Cell;
        Cell.setFillColor(sf::Color::Green);
        Cell.setSize({float(Cell_Size), float(Cell_Size)});

        for(int i = 0; i < ROW; ++i)
        {
            for(int j = 0; j < COL; ++j)
            {   
                if(Terrain[i][j] == CELL::LAND) Cell.setFillColor(sf::Color(250, 173, 39));
                if(Terrain[i][j] == CELL::TREE) Cell.setFillColor(sf::Color::Green);
                if(Terrain[i][j] == CELL::ORE) Cell.setFillColor(sf::Color(128, 128, 128));
                if(Terrain[i][j] == CELL::WATER) Cell.setFillColor(sf::Color::Blue);

                Cell.setPosition({float(j * Cell_Size), float(i * Cell_Size)});
                window.draw(Cell);
            }
        }

        if(HoverCell.x != -1)
        {
            Cell.setFillColor(sf::Color(40, 210, 40, 95));
            Cell.setPosition(float(Cell_Size * HoverCell . y), float(Cell_Size * HoverCell.x));
            window.draw(Cell);
        }
    }