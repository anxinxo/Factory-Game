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

    sf::VertexArray vertices(sf::Quads);

    for (int wy = startY; wy <= endY; ++wy)
    {
        for (int wx = startX; wx <= endX; ++wx)
        {
            CELL& cell = WORLD.GetCell(wx, wy);
            
            sf::Color color;
            switch (cell.CellType)
            {
                case TTYPE::GRASS: color = sf::Color::Green; break;
                case TTYPE::ROCK:  color = sf::Color(120,120,120); break;
                case TTYPE::SAND:  color = sf::Color(194,178,128); break;
                case TTYPE::WATER: color = sf::Color::Blue; break;
            }

            float x = wx * cellSize;
            float y = wy * cellSize;

            vertices.append(sf::Vertex({x, y}, color));
            vertices.append(sf::Vertex({x + cellSize, y}, color));
            vertices.append(sf::Vertex({x + cellSize, y + cellSize}, color));
            vertices.append(sf::Vertex({x, y + cellSize}, color));
        }
    }

    window.draw(vertices);
}