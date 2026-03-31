#pragma once

#include <SFML/Graphics.hpp>
#include "../Header/Map.hpp"

class Renderer
{
public:
    void draw_Map(sf::RenderWindow &window, const Map &MAP);

};