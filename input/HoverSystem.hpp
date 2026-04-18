#pragma once

#include <SFML/Graphics.hpp>
#include "core/World.hpp"
#include "input/MouseWorld.hpp"
#include <vector>

class HoverSystem
{
public:
    void Update(const MouseWorld& MW, const World& W, int Lx, int Rx, int Uy, int Dy, bool HoverNow);

    const std::vector<sf::Vector2i>& getHoveredTiles() const;
    bool Isempty() const;
private:
    std::vector<sf::Vector2i> HoveredTiles;
};