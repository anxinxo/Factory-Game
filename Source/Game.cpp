#include "../Header/Game.hpp"

    Game::Game(int WIDTH, int HEIGHT, int FPS, std::string Window_Name)
    : window(sf::VideoMode(WIDTH, HEIGHT), Window_Name)
    {
        this->window.setFramerateLimit(FPS);
    }

    void Game::Run()
    {
        while(this->window.isOpen())
        {
            Game::Process_Event();
            Game::Update();
            Game::Rendering();
        }
    }

    void Game::Process_Event()
    {
        while(this->window.pollEvent(this->event))
        {
            if(this->event.type == sf::Event::Closed) this->window.close();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) this->window.close();
        }
    }

    void Game::Update()
    {
        float delta_time = this->clock.restart().asSeconds();
    }

    void Game::Rendering()
    {
        this->window.clear();

        this->window.display();
    }