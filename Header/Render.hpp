#pragma once

#include <SFML/Graphics.hpp>
#include "../Header/World.hpp"

class Renderer
{
public:
    void draw_World(sf::RenderWindow &window, World& WORLD, int cellSize);
};