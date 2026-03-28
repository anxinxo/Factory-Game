#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include <memory>
#include <string>

class Sprite_Manager
{
private:
    std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures;

public:
    void LoadTexture(const std::string& name, const std::string& path);
    
    std::shared_ptr<sf::Texture> GetTexture(const std::string& name);

    bool Exist(const std::string& Name) const;

};