#include "../Header/SpriteManager.hpp"

    void Sprite_Manager::LoadTexture(const std::string& Name, const std::string& path)
    {
        if(textures.find(Name) != textures.end()) return;

        std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();

        if(!texture->loadFromFile(path))
        {
            std::cout << "NGU NHU CHO DCM";
            return;
        }

        textures[Name] = texture;
    }

    std::shared_ptr<sf::Texture> Sprite_Manager::GetTexture(const std::string& Name)
    {
        if(textures.find(Name) == textures.end())
        {
            std::cout << "Co del, m lua tao a";
            return nullptr;
        }

        return textures[Name];
    }

    bool Sprite_Manager::Exist(const std::string& Name) const
    {
        return textures.find(Name) != textures.end();
    }