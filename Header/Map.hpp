#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Map
{
private:

    enum class CELL
    {
        LAND,
        WATER,
        TREE,
        ORE
    };

    int WIDTH, HEIGHT, ROW, COL;
    int Cell_Size;

    sf::Vector2i HoverCell;
    std::vector<std::vector<CELL>> Terrain;

public:
    Map(int _W, int _H, int _CellSize);

    void Hovering_Cell(sf::Vector2f realPos);

    void Updating();

    void drawby(sf::RenderWindow& window);
};