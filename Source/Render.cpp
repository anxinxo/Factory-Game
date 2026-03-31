#include "../Header/Render.hpp"

    void Renderer::draw_Map(sf::RenderWindow &window, const Map &MAP)
    {
        const sf::Vector2i RC = MAP.GetRC();
        int Size = MAP.Get_Cell_Size();
        sf::RectangleShape title;
        title.setSize({(float)Size, (float)Size});

        for(int i = 0; i < RC.x; ++i)
        {
            for(int j = 0; j < RC.y; ++j)
            {   
                switch (MAP.getType(i, j))
                {
                    case TTYPE::GRASS:
                    {
                        title.setFillColor(sf::Color::Green);
                        break;
                    }

                    case TTYPE::ROCK:
                    {
                        title.setFillColor(sf::Color(120, 120, 120));
                        break;
                    }

                    case TTYPE::SAND:
                    {
                        title.setFillColor(sf::Color(194, 178, 128));
                        break;
                    }

                    case TTYPE::WATER:
                    {
                        title.setFillColor(sf::Color::Blue);
                        break;
                    }
                }
                title.setPosition(j * Size, i * Size);

                window.draw(title);
            }
        }
    }