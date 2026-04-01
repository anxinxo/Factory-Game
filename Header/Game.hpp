#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "../Header/SpriteManager.hpp"
#include "../Header/Render.hpp"
#include "../Header/World.hpp"

class Game
{
private:
    sf::RenderWindow window;
    sf::Event event;
    sf::Clock clock;

    Sprite_Manager SpriteManager;
    Renderer RenderMap;

    int cellSize;
    World WORLD;

    bool Dragging;
    sf::Vector2i LastMousePos;

    void Process_Event();
    void Update();
    void Rendering();

public:
    Game(int WIDTH, int HEIGHT, int FPS, std::string Window_Name);
    void Run();
};