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
            std::vector<int> c(COL, 0);
            Grid.emplace_back(c);
        }
    }

    void Map::drawby(sf::RenderWindow& window)
    {   
        sf::RectangleShape Cell;
        Cell.setFillColor(sf::Color::Green);
        Cell.setSize({float(Cell_Size), float(Cell_Size)});
        Cell.setOutlineColor(sf::Color::White);
        Cell.setOutlineThickness(1);

        for(int i = 0; i < ROW; ++i)
        {
            for(int j = 0; j < COL; ++j)
            {
                Cell.setPosition({float(j * Cell_Size), float(i * Cell_Size)});
                window.draw(Cell);
            }
        }
    }