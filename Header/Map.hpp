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

    std::vector<std::vector<int>> Hover;
    std::vector<std::vector<CELL>> Grid;

public:
    Map(int _W, int _H, int _CellSize);

    void HoverCell(sf::Vector2f realPos);

    void Updating();

    void drawby(sf::RenderWindow& window);
};