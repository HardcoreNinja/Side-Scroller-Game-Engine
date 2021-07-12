#include "Header.h"
#include "MainMenu.h"

/*Initializers*/
void MainMenu::initBackground()
{
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->gameDetails->window->getSize().x), 
			static_cast<float>(this->gameDetails->window->getSize().y)
		)
		);

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Background/background.jpg"))
		throw ("ERROR::MAIN_MENU::FAILED_TO_LOAD::background.jpg");

	this->background.setTextureRect(
		sf::IntRect(
			0, 0,
			this->backgroundTexture.getSize().x,
			this->backgroundTexture.getSize().y
		)
	);

	this->background.setTexture(&this->backgroundTexture);
}

/*Constructor & Destructor*/
MainMenu::MainMenu(GameDetails* game_details)
	: State(game_details)
{
	this->initBackground();
}
MainMenu::~MainMenu()
{
}

/*Update Functions*/
void MainMenu::update(const float& dt)
{
}

/*Render Functions*/
void MainMenu::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->gameDetails->window;

	target->draw(this->background);
}
