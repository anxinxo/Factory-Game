#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <ultilities/MathGrid.hpp>
#include <rendering/SpriteManager.hpp>
#include <rendering/Render.hpp>
#include <core/World.hpp>
#include <input/MouseWorld.hpp>
#include <input/HoverSystem.hpp>

class Game
{
private:
    sf::RenderWindow window;
    sf::Event event;
    sf::Clock clock;

    Sprite_Manager SpriteManager;
    Renderer RenderMap;

    int TILE_SIZE;
    World WORLD;
    MouseWorld MOUSEWORLD;
    HoverSystem HOVERSYSTEM;

    bool Dragging;
    bool HasLast;
    sf::Vector2f LastMouseWorldPos;
    sf::Vector2f DragAnchorWorld;
    sf::Vector2f DragAnchorCenter;
    sf::View DragStartView;

    float zoomLevel = 1.0f;
    const float zoomStep = 1.1f;
    const float MinZoom = 0.2f;
    const float MaxZoom = 7.0f;
    sf::Vector2f BaseViewSize;

    void Fix_view();
    void Process_Event();
    void Update();
    void Rendering();

public:
    Game(int WIDTH, int HEIGHT, int FPS, std::string Window_Name);
    void Run();
};