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
		sf::Vector2f(
			static_cast<float>(this->gameDetails->window->getSize().x) / 2.f,
			static_cast<float>(this->gameDetails->window->getSize().y) / 2.f + 200.f),//Button Position
		sf::Vector2f(400.f, 150.f),                                                   //Button Size
		this->gameDetails->font,                                                      //Text Font
		"back",                                                                       //String                     
		50,                                                                           //Character Size 
		sf::Color::White,                                                             //Text Idle Color
		sf::Color::Blue,                                                              //Text Hover Color
		sf::Color::Red                                                                //Text Click Color
		);

	this->buttonMap["Back"] = std::move(this->button);
}

void Settings::initDropDowns()
{
	std::vector<std::string> fullscreenStringVector { "yes", "no" };
	this->dropdownMap["Fullscreen"] = std::make_unique<GUI::DropDown>(
		sf::Vector2f(
			static_cast<float>(this->gameDetails->window->getSize().x) / 2.f,
			20.f), //Dropdown Position
		sf::Vector2f(400.f, 150.f),                                                    //Dropdown Size
		this->gameDetails->font,                                                       //Dropdown Text Font
		50,                                                                            //Dropdown Text Character Size
		fullscreenStringVector.data(),                                                        //Dropdown String Vector
		this->inputTime,                                                               //Input Time
		this->maxInputTime,                                                            //Max Input Time
		static_cast<unsigned>(fullscreenStringVector.size())                          //Size of String Vector
		);
}

/*Constructor & Destructor*/
Settings::Settings(GameDetails* game_details)
	: State(game_details)
{
	this->initBackground();
	this->initButtons();
	this->initDropDowns();
}
Settings::~Settings()
{
}

/*Update Functions*/
void Settings::updateDropdowns(const float& dt)
{
	for (auto& i : this->dropdownMap)
		i.second->update(this->mousePositionWindow, dt);
}
void Settings::updateButtons()
{
	if (this->buttonMap["Back"]->getButtonClickState() && this->getInputTime())
		this->setEndStateTrue();
}
void Settings::update(const float& dt)
{
	this->updateInputTime(dt);
	this->updateMousePosition();

	this->updateDropdowns(dt);
	this->updateButtonMap();
	this->updateButtons();	
}

/*Render Functions*/
void Settings::renderDropdowns(sf::RenderTarget& target)
{
	for (auto& i : this->dropdownMap)
		i.second->render(target);
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

	/*Background*/
	target->draw(this->background);

	/*Dropdowns*/
	this->renderDropdowns(*target);

	/*Buttons*/
	this->renderButtonMap(*target);
}
