#include "Header.h"
#include "Settings.h"

/*Initializers*/
void Settings::initBackground()
{
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->gameDetails->window->getSize().x),
			static_cast<float>(this->gameDetails->window->getSize().y)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Background/background_2.jpg"))
		throw ("ERROR::MAIN_MENU::FAILED_TO_LOAD::background_2.jpg");

	this->background.setTextureRect(
		sf::IntRect(
			0, 0,
			this->backgroundTexture.getSize().x,
			this->backgroundTexture.getSize().y
		)
	);

	this->background.setTexture(&this->backgroundTexture);
}
void Settings::initButtons()
{
	this->button = std::make_unique<GUI::Button>(
		sf::Vector2f(static_cast<float>(this->gameDetails->window->getSize().x) / 2.f, static_cast<float>(this->gameDetails->window->getSize().y) / 2.f + 200.f), //Button Position
		sf::Vector2f(100.f, 200.f),                                                                                                                       
		this->gameDetails->font, 
		"back",
		50,
		sf::Color::White,
		sf::Color::Blue,
		sf::Color::Red
		);

	this->buttonMap["Back"] = std::move(this->button);
}

/*Constructor & Destructor*/
Settings::Settings(GameDetails* game_details)
	: State(game_details)
{
	this->initBackground();
	this->initButtons();
}
Settings::~Settings()
{
}

/*Update Functions*/
void Settings::updateButtons()
{
	if (this->buttonMap["Back"]->getButtonClickState())
		this->setEndStateTrue();
}
void Settings::update(const float& dt)
{
	this->updateMousePosition();
	this->updateButtonMap();
	this->updateButtons();
}

void Settings::renderButtonMap(sf::RenderTarget& target)
{
	for (auto& i : this->buttonMap)
		i.second->render(target);
}
void Settings::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->gameDetails->window;

	target->draw(this->background);
	this->renderButtonMap(*target);
}
