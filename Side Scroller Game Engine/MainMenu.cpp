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
		sf::Vector2f(
			static_cast<float>(this->gameDetails->window->getSize().x) / 2.f, 
			static_cast<float>(this->gameDetails->window->getSize().y) / 2.f), //Button Position
		sf::Vector2f(400.f, 150.f),                                            //Button Size
		this->gameDetails->font,                                               //Text Font
		"settings",                                                            //String                     
		50,                                                                    //Character Size 
		sf::Color::White,                                                      //Text Idle Color
		sf::Color::Blue,                                                       //Text Hover Color
		sf::Color::Red                                                         //Text Click Color
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

/*Setters*/
void MainMenu::setInitializers()
{
	this->initBackground();
	this->initButtons();
}

/*Update Functions*/
void MainMenu::updateButtons()
{
	if (this->buttonMap["Settings"]->getButtonClickState() && this->getInputTime())
		this->gameDetails->states->push_back(std::make_unique<Settings>(this->gameDetails));
}
void MainMenu::update(const float& dt)
{
	this->updateMousePosition();
	this->updateButtonMap();
	this->updateButtons();
	this->updateInputTime(dt);
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