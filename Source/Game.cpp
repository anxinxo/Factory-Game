#include "../Header/Game.hpp"

Game::Game(int WIDTH, int HEIGHT, int FPS, std::string Window_Name)
: window(sf::VideoMode(WIDTH, HEIGHT), Window_Name),
WORLD(28),
TILE_SIZE(32)
{
    this->window.setFramerateLimit(FPS);
    BaseViewSize = window.getView().getSize();
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
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left)
        {
            Dragging = true;
            
            DragStartView = window.getView();

            sf::Vector2i pixel = sf::Mouse::getPosition(window);

            DragAnchorWorld  = window.mapPixelToCoords(pixel);
            DragAnchorCenter = DragStartView.getCenter();
        }

        // Thả chuột
        if (event.type == sf::Event::MouseButtonReleased &&
            event.mouseButton.button == sf::Mouse::Left)
        {
            Dragging = false;
        }

        //zoom in / out
        if (event.type == sf::Event::MouseWheelScrolled)
        {
            // Tọa độ world trước khi zoom (tại vị trí chuột)
            sf::Vector2i pixel = sf::Mouse::getPosition(window);

            sf::View view = window.getView();
            sf::Vector2f before = window.mapPixelToCoords(pixel, view);

            if(event.mouseWheelScroll.delta > 0) 
                zoomLevel /= zoomStep;
            else
                zoomLevel *= zoomStep;  
            
            zoomLevel = std::clamp(zoomLevel, MinZoom, MaxZoom);

            view.setSize(BaseViewSize * zoomLevel);
            window.setView(view);

            sf::Vector2f after = window.mapPixelToCoords(pixel);
            sf::Vector2f offset = before - after;
            view.move(offset);
            window.setView(view);
        }
    }
}

void Game::Update()
{
    float delta_time = this->clock.restart().asSeconds();
    
    if (Dragging)
    {
        sf::Vector2i pixel = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(pixel, DragStartView);

        sf::Vector2f offset = DragAnchorWorld - worldPos;

        sf::View view = DragStartView;
        view.setCenter(DragAnchorCenter + offset);
        window.setView(view);
    }
    else
    {
        HasLast = false;
    }

    MOUSEWORLD.Update(window, window.getView(), TILE_SIZE, 32);
    HOVERSYSTEM.Update(MOUSEWORLD, WORLD, 1, 1, 1, 1, true);
    
    sf::Vector2f Mpos = MOUSEWORLD.getWorldPos();
    sf::Vector2i Cpos = MOUSEWORLD.getChunkPos();
    sf::Vector2i Tpos = MOUSEWORLD.getTilePos();
    system("cls");
    std::cout << "Mouse Position: " << Mpos.x << " " << Mpos.y << '\n';
    std::cout << "Chunk Position: " << Cpos.x << " " << Cpos.y << '\n';
    std::cout << "Tile Position: " << Tpos.x << " " << Tpos.y << '\n';
}

void Game::Rendering()
{
    this->window.clear();

    // LẤY vị trí camera (center view)
    sf::View view = window.getView();
    sf::Vector2f center = view.getCenter();

    int wx = center.x / TILE_SIZE;
    int wy = center.y / TILE_SIZE;

    int cx = wx / Chunk::SIZE;
    int cy = wy / Chunk::SIZE;

    // YÊU CẦU world tạo chunk quanh camera
    for (int dx = -3; dx <= 3; ++dx)
    for (int dy = -3; dy <= 3; ++dy)
    {
        WORLD.GetChunk(cx + dx, cy + dy);
    }

    // Sau đó mới render
    RenderMap.draw_World(window, WORLD, TILE_SIZE);
    RenderMap.draw_Hover(window, HOVERSYSTEM, TILE_SIZE);

    this->window.display();
}