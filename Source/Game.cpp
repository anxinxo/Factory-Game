#include "../Header/Game.hpp"

    Game::Game(int WIDTH, int HEIGHT, int FPS, std::string Window_Name)
    : window(sf::VideoMode(WIDTH, HEIGHT), Window_Name),
    cellSize(32)
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

            // Bắt đầu kéo
            if(event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left)
            {
                Dragging = true;
                LastMousePos = sf::Mouse::getPosition(window);
            }

            // Thả chuột
            if(event.type == sf::Event::MouseButtonReleased &&
            event.mouseButton.button == sf::Mouse::Left)
            {
                Dragging = false;
            }

            // Đang kéo
            if(event.type == sf::Event::MouseMoved && Dragging)
            {
                sf::Vector2i newPos = sf::Mouse::getPosition(window);
                sf::Vector2i delta = LastMousePos - newPos;

                sf::View view = window.getView();
                view.move((float)delta.x, (float)delta.y);
                window.setView(view);

                LastMousePos = newPos;
            }

            if (event.type == sf::Event::MouseWheelScrolled)
            {
                sf::View view = window.getView();

                // Tọa độ world trước khi zoom (tại vị trí chuột)
                sf::Vector2i pixel = sf::Mouse::getPosition(window);
                sf::Vector2f before = window.mapPixelToCoords(pixel);

                // Hệ số zoom
                if (event.mouseWheelScroll.delta > 0)
                    view.zoom(0.9f);   // zoom in
                else
                    view.zoom(1.1f);   // zoom out

                window.setView(view);

                // Tọa độ world sau khi zoom
                sf::Vector2f after = window.mapPixelToCoords(pixel);

                // Dịch camera để điểm dưới chuột giữ nguyên
                sf::Vector2f offset = before - after;
                view.move(offset);
                window.setView(view);
            }
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