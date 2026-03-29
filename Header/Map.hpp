#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Map
{
private:
    int WIDTH, HEIGHT, ROW, COL;
    int Cell_Size;

    std::vector<std::vector<int>> Grid;

public:
    Map(int _W, int _H, int _CellSize);

    void HoverCell(sf::Vector2f realPos);

    void Updating();

    void drawby(sf::RenderWindow& window);
};