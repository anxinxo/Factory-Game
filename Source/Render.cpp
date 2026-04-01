#include "../Header/Render.hpp"

void Renderer::draw_World(sf::RenderWindow& window, World& WORLD, int cellSize)
{
    sf::View view = window.getView();
    sf::FloatRect visible(
        view.getCenter() - view.getSize() / 2.f,
        view.getSize()
    );

    int startX = visible.left / cellSize - 1;
    int startY = visible.top  / cellSize - 1;
    int endX   = (visible.left + visible.width)  / cellSize + 1;
    int endY   = (visible.top  + visible.height) / cellSize + 1;

    sf::RectangleShape tile({(float)cellSize, (float)cellSize});

    for (int wy = startY; wy <= endY; ++wy)
    {
        for (int wx = startX; wx <= endX; ++wx)
        {
            CELL& cell = WORLD.GetCell(wx, wy);

            switch (cell.CellType)
            {
                case TTYPE::GRASS: tile.setFillColor(sf::Color::Green); break;
                case TTYPE::ROCK:  tile.setFillColor(sf::Color(120,120,120)); break;
                case TTYPE::SAND:  tile.setFillColor(sf::Color(194,178,128)); break;
                case TTYPE::WATER: tile.setFillColor(sf::Color::Blue); break;
            }

            tile.setPosition(wx * cellSize, wy * cellSize);
            window.draw(tile);
        }
    }
}