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
        
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f realPos = window.mapPixelToCoords(pixelPos);
    }

    void Game::Rendering()
    {
        this->window.clear();

       // LẤY vị trí camera (center view)
        sf::View view = window.getView();
        sf::Vector2f center = view.getCenter();

        int cellSize = 20;

        int wx = center.x / cellSize;
        int wy = center.y / cellSize;

        int cx = wx / Chunk::SIZE;
        int cy = wy / Chunk::SIZE;

        // YÊU CẦU world tạo chunk quanh camera
        for (int dx = -3; dx <= 3; ++dx)
        for (int dy = -3; dy <= 3; ++dy)
        {
            WORLD.GetChunk(cx + dx, cy + dy);
        }

        // Sau đó mới render
        RenderMap.draw_World(window, WORLD, cellSize);

        this->window.display();
    }