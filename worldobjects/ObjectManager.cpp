#include <worldobjects/ObjectManager.hpp>

void ObjectManager::addObject(std::unique_ptr<worldobjects> obj)
{
    objects.push_back(std::move(obj));
}

void ObjectManager::update(float dt)
{
    for (auto& obj : objects)
        obj->update(dt);
}

void ObjectManager::draw(sf::RenderWindow& window)
{
    for (auto& obj : objects)
        obj->draw(window);
}