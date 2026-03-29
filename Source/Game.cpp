#include "../Header/Game.hpp"

    Game::Game(int WIDTH, int HEIGHT, int FPS, std::string Window_Name)
    : window(sf::VideoMode(WIDTH, HEIGHT), Window_Name),
    MAP(WIDTH, HEIGHT, 20)
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
        
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f realPos = window.mapPixelToCoords(pixelPos);

        MAP.Updating();
        MAP.HoverCell(realPos);
    }

    void Game::Rendering()
    {
        this->window.clear();

        MAP.drawby(window);

        this->window.display();
    }