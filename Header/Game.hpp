#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "../Header/SpriteManager.hpp"
#include "../Header/Render.hpp"
#include "../Header/Map.hpp"

class Game
{
private:
    sf::RenderWindow window;
    sf::Event event;
    sf::Clock clock;

    Sprite_Manager SpriteManager;
    Renderer RenderMap;    
    Map MAP;

    void Process_Event();
    void Update();
    void Rendering();

public:
    Game(int WIDTH, int HEIGHT, int FPS, std::string Window_Name);
    void Run();
};