#include "Game.h"

void Game::initValues()
{
    // m_gameState = GameState::Menu;
    m_gameState = GameState::Play;
    m_maxFPS = 0;
    m_minFPS = (size_t)-1;
}

void Game::initWindow()
{
    sf::VideoMode vm = DEBUG_VIEW ? sf::VideoMode(800, 600) : sf::VideoMode::getDesktopMode();
    // m_contextSettings
    m_window = new sf::RenderWindow(vm, "Shooter Game", DEBUG_VIEW ? sf::Style::Default : sf::Style::Fullscreen, m_contextSettings);
    // m_window->setFramerateLimit(240);
}

void Game::initPlayer()
{
    auto size = m_window->getSize();
    float width = static_cast<float>(size.x);
    float height = static_cast<float>(size.y);
    m_player.setPosition(sf::Vector2f(width/2.f, height/2.f));
}

void Game::initObjects()
{
    this->initPlayer();
}

Game::Game()
{
    this->initValues();
    this->initWindow();
    this->initObjects();
}

Game::~Game()
{
    delete m_window;
}

void Game::updateCurrentrTick()
{
    ++m_currentTick;
}

void Game::updateDeltaTime()
{
    m_dt = m_deltaTimeClock.restart().asSeconds();
}

void Game::pollEvent()
{
    while(m_window->pollEvent(m_currentEvent)){
        switch (m_currentEvent.type){
        case sf::Event::Closed:
            m_window->close();
            break;
        case sf::Event::KeyPressed:
            if(m_currentEvent.key.code == sf::Keyboard::Escape)
                m_window->close();
            break;
        default:
            break;
        }
    }
}

void Game::updateMenuStage()
{

}

void Game::updatePlayStage()
{
    m_player.update();
}

void Game::update()
{
    if(m_currentTick % 100 == 1)
    {
        int fps = 1.f/m_dt;
        if(fps > m_maxFPS) m_maxFPS = fps;
        if(fps < m_minFPS) m_minFPS = fps;

        printf("\r                              \r");
        printf("frame: % 9lld, fps: % 6d, (min: %lld, max: %lld)", m_currentTick, fps, m_minFPS, m_maxFPS);
        fflush(stdout);
    }

    switch (m_gameState) {
    case GameState::Menu: this->updateMenuStage(); break;
    case GameState::Play: this->updatePlayStage(); break;
    default: printf("unknown game state, can't update\n"); break;
    }
}

void Game::renderMenuStage()
{

}

void Game::renderPlayStage()
{
    m_player.render(m_window);

}

void Game::render()
{
    m_window->clear(BACKGROUND_SF_COLOR);

    switch (m_gameState) {
    case GameState::Menu: this->renderMenuStage(); break;
    case GameState::Play: this->renderPlayStage(); break;
    default: printf("unknown game state, can't render\n"); break;
    }

    m_window->display();
}

bool Game::running() const noexcept
{
    return m_window->isOpen();
}

void Game::play()
{
    Game game;
    while(game.running())
    {
        game.updateCurrentrTick();
        game.updateDeltaTime();

        game.pollEvent();
        game.update();
        game.render();
    }
    printf("\n");
}
