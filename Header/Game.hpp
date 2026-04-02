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
    bool HasLast;
    sf::Vector2f LastMouseWorldPos;
    sf::Vector2f DragAnchorWorld;
    sf::Vector2f DragAnchorCenter;
    sf::View DragStartView;

    float zoomLevel = 1.0f;
    const float zoomStep = 1.1f;
    const float MinZoom = 0.2f;
    const float MaxZoom = 5.0f;
    sf::Vector2f BaseViewSize;

    void Process_Event();
    void Update();
    void Rendering();

public:
    Game(int WIDTH, int HEIGHT, int FPS, std::string Window_Name);
    void Run();
};