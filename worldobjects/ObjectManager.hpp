#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <worldobjects/worldobjects.hpp>

class ObjectManager
{
    std::vector<std::unique_ptr<worldobjects>> objects;

public:
    void update(float dt);
    void draw(sf::RenderWindow& window);

    void addObject(std::unique_ptr<worldobjects> obj);
};