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

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Background/background_1.jpg"))
		throw ("ERROR::MAIN_MENU::FAILED_TO_LOAD::background_1.jpg");

	this->background.setTextureRect(
		sf::IntRect(
			0, 0,
			this->backgroundTexture.getSize().x,
			this->backgroundTexture.getSize().y
		)
	);

	this->background.setTexture(&this->backgroundTexture);
}
void MainMenu::initButtons()
{
	this->button = std::make_unique<GUI::Button>(
		sf::Vector2f(static_cast<float>(this->gameDetails->window->getSize().x) / 2.f, static_cast<float>(this->gameDetails->window->getSize().y) / 2.f), //Button Position
		sf::Vector2f(100.f, 50.f),
		this->gameDetails->font,
		"settings",
		50,
		sf::Color::White,
		sf::Color::Blue,
		sf::Color::Red
		); 

	this->buttonMap["Settings"] = std::move(this->button);
}

/*Constructor & Destructor*/
MainMenu::MainMenu(GameDetails* game_details)
	: State(game_details)
{
	this->initBackground();
	this->initButtons();
}
MainMenu::~MainMenu()
{
}

/*Update Functions*/
void MainMenu::updateButtons()
{
	if (this->buttonMap["Settings"]->getButtonClickState())
		this->gameDetails->states->push_back(std::make_unique<Settings>(this->gameDetails));
}
void MainMenu::update(const float& dt)
{
	this->updateMousePosition();
	this->updateButtonMap();
	this->updateButtons();
}

/*Render Functions*/
void MainMenu::renderButtonMap(sf::RenderTarget& target)
{
	for (auto& i : this->buttonMap)
		i.second->render(target);
}
void MainMenu::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->gameDetails->window;

	target->draw(this->background);
	this->renderButtonMap(*target);
}
