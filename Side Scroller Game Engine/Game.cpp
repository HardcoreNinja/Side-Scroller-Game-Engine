#include "Header.h"
#include "Game.h"

/*Initializers*/
void Game::initGraphicsSettings()
{
    this->graphicsSettings = std::make_unique<GraphicsSettings>();

    this->graphicsSettings->loadFromFile();
}
void Game::initWindow()
{
    auto style = this->graphicsSettings->getFullScreen() ? sf::Style::Fullscreen : sf::Style::Default;
    
    this->window = std::make_unique<sf::RenderWindow>(
        this->graphicsSettings->getVideoMode(),
        this->graphicsSettings->getTitle(),
        style, 
        this->graphicsSettings->getContextSettings()
        );

    this->window->setVerticalSyncEnabled(this->graphicsSettings->getVSync());
    this->window->setFramerateLimit(this->graphicsSettings->getFrameRateLimit());
}

/*Constructor & Destructor*/
Game::Game()
{
    this->initGraphicsSettings();
	this->initWindow();
}
Game::~Game()
{
}

/*Update Functions*/
void Game::updateDeltaTime()
{
	this->dt = this->dtClock.restart().asSeconds();

    std::cout << "Delta Time: " << this->dt << '\n';
}
void Game::update()
{
    this->updateDeltaTime();
    sf::Event event;
    while (this->window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            this->window->close();
    }
}

/*Render Functions*/
void Game::render()
{
    this->window->clear(sf::Color::Magenta);

   this->window->display();
}

/*Run Function*/
void Game::run()
{
    while (this->window->isOpen())
    {
        this->update();
        this->render();
    }
}
