#pragma once

#include <SFML/Graphics.hpp>
#include "../Header/World.hpp"
#include "../Header/HoverSystem.hpp"

class Renderer
{
public:
    void draw_World(sf::RenderWindow& window, World& WORLD, int TILE_SIZE);
    void draw_Hover(sf::RenderWindow& window, HoverSystem& HOVERSYSTEM, int TILE_SIZE);
};