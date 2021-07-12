#include "Header.h"
#include "Game.h"

/*Initializers*/
void Game::initWindow()
{
	this->window = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "Game Engine");

    this->window->setFramerateLimit(120);
}

/*Constructor & Destructor*/
Game::Game()
{
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
