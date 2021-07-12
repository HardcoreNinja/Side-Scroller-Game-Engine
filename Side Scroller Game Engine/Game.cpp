#include "Header.h"
#include "Game.h"

/*Initializers*/
void Game::initSupportedKey()
{
    std::ifstream ifs("Config/supported_keys.ini"); 
    std::string key = "";
    int keyValue = 0;

    if (ifs.is_open())
    {
        while (ifs >> key)
        {
            this->supportedKeys[key] = keyValue; 
            keyValue++;
        }
    }
    ifs.close();

    /*Debug
    for (auto& i : this->supportedKeys)
        std::cout << i.first << " " << i.second << '\n';*/
}
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
void Game::initGameDetails()
{
    this->gameDetails.graphicsSettings = this->graphicsSettings.get();
    this->gameDetails.window = this->window.get(); 
    this->gameDetails.states = &this->states;
}
void Game::initStates()
{
    this->states.push_back(std::make_unique<MainMenu>(&this->gameDetails));
}

/*Constructor & Destructor*/
Game::Game()
    : gameDetails(this->supportedKeys)
{
    this->initSupportedKey();
    this->initGraphicsSettings();
	this->initWindow();
    this->initGameDetails();
    this->initStates();
}
Game::~Game()
{
}

/*Update Functions*/
void Game::updateDeltaTime()
{
	this->dt = this->dtClock.restart().asSeconds();

    //std::cout << "Delta Time: " << this->dt << '\n';
}
void Game::update()
{
    this->updateDeltaTime();
    if (!this->states.empty())
    {
        sf::Event event;
        while (this->window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                this->window->close();

        }

        this->states.back()->update(this->dt);
    }
}

/*Render Functions*/
void Game::render()
{
    this->window->clear(sf::Color::Magenta);
    if(!this->states.empty())
    this->states.back()->render();
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
