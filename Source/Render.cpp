#include "../Header/Render.hpp"

void Renderer::draw_World(sf::RenderWindow& window, World& WORLD, int TILE_SIZE)
{   
    sf::View view = window.getView();
    sf::FloatRect visible(
        view.getCenter() - view.getSize() / 2.f,
        view.getSize()
    );

    int startX = visible.left / TILE_SIZE - 1;
    int startY = visible.top  / TILE_SIZE - 1;
    int endX   = (visible.left + visible.width)  / TILE_SIZE + 1;
    int endY   = (visible.top  + visible.height) / TILE_SIZE + 1;

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

            float x = wx * TILE_SIZE;
            float y = wy * TILE_SIZE;

            vertices.append(sf::Vertex({x, y}, color));
            vertices.append(sf::Vertex({x + TILE_SIZE, y}, color));
            vertices.append(sf::Vertex({x + TILE_SIZE, y + TILE_SIZE}, color));
            vertices.append(sf::Vertex({x, y + TILE_SIZE}, color));
        }
    }

    window.draw(vertices);
}

void Renderer::draw_Hover(sf::RenderWindow& window, HoverSystem& HOVERSYSTEM, int TILE_SIZE)
{
    sf::RectangleShape hoverRect;
    hoverRect.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));

    float worldPerPixel = window.mapPixelToCoords({1,0}).x - window.mapPixelToCoords({0,0}).x;

    float thickness = 2.0f * worldPerPixel;
    hoverRect.setOutlineThickness(thickness);

    hoverRect.setOutlineColor(sf::Color(255, 220, 0));
    hoverRect.setFillColor(sf::Color(255, 220, 0, 45));

    const auto& tiles = HOVERSYSTEM.getHoveredTiles();
    for (const auto& t : tiles) 
    {
        hoverRect.setPosition(t.x * TILE_SIZE, t.y * TILE_SIZE);
        window.draw(hoverRect);
    }
}