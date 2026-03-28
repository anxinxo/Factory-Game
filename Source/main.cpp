#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Header/Game.hpp"

const int WIDTH = 1280;
const int HEIGHT = 720;
const int FPS = 60;

int main()
{
    Game GAME(WIDTH, HEIGHT, FPS, "default");

    GAME.Run();
}
