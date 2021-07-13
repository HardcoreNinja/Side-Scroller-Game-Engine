#include "Header.h"
#include "Settings.h"

/*Initializers*/
void Settings::initVariables()
{
	this->videoModes = sf::VideoMode::getFullscreenModes();
}
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
void Settings::initTitles()
{
	float positionX = 20.f;
	float positionY = 70.f;

	unsigned characterSize = 10;

	this->titles.setFont(*this->gameDetails->font);
	this->titles.setCharacterSize(characterSize);
	this->titles.setFillColor(sf::Color::White);
	this->titles.setPosition(sf::Vector2f(positionX, positionY));
	this->titles.setString("resolutions \n\n\n\nfullscreen \n\n\n\nvsync \n\n\n\nanti aliasing \n\n\n\n");
}
void Settings::initButtons()
{
	float positionX = 125.f;
	float positionY = static_cast<float>(this->gameDetails->window->getSize().y);
	float offsetY = 50.f;

	float sizeX = 200.f;
	float sizeY = 50.f;

	unsigned characterSize = 20;

	this->button = std::make_unique<GUI::Button>(
		sf::Vector2f(positionX, positionY - offsetY), //Button Position
		sf::Vector2f(sizeX, sizeY),                   //Button Size
		this->gameDetails->font,                      //Text Font
		"back",                                       //String                     
		characterSize,                                //Character Size 
		sf::Color::White,                             //Text Idle Color
		sf::Color::Blue,                              //Text Hover Color
		sf::Color::Red                                //Text Click Color
		);

	this->buttonMap["Back"] = std::move(this->button);
}
void Settings::initDropDowns()
{
	float positionX = 350.f;
	float positionY = 85.f;
	float offsetY = 45;

	float sizeX = 100.f;
	float sizeY = 25.f;
	
	unsigned characterSize = 10;

	std::vector<std::string> resolutionStringVector;
	for (auto& i : this->videoModes)
		resolutionStringVector.push_back(std::to_string(i.width) + " x " + std::to_string(i.height));
	this->dropdownMap["Resolution"] = std::make_unique<GUI::DropDown>(
		sf::Vector2f(positionX, positionY + (offsetY * 0)),                                   //Dropdown Position
		sf::Vector2f(sizeX, sizeY),															  //Dropdown Size
		this->gameDetails->font,                                                              //Dropdown Text Font
		characterSize,                                                                        //Dropdown Text Character Size
		resolutionStringVector,                                                               //Dropdown String Vector
		this->inputTime,                                                                      //Input Time
		this->maxInputTime,                                                                   //Max Input Time
		static_cast<unsigned>(resolutionStringVector.size())                                  //Size of String Vector
		);

	std::vector<std::string> fullscreenStringVector { "yes", "no" };
	this->dropdownMap["Fullscreen"] = std::make_unique<GUI::DropDown>(
		sf::Vector2f(positionX, positionY + (offsetY * 1)),                                   //Dropdown Position
		sf::Vector2f(sizeX, sizeY),                                                           //Dropdown Size
		this->gameDetails->font,                                                              //Dropdown Text Font
		characterSize,                                                                        //Dropdown Text Character Size
		fullscreenStringVector,                                                               //Dropdown String Vector
		this->inputTime,                                                                      //Input Time
		this->maxInputTime,                                                                   //Max Input Time
		static_cast<unsigned>(fullscreenStringVector.size())                                  //Size of String Vector
		);

	std::vector<std::string> vSyncStringVector{ "yes", "no" };
	this->dropdownMap["VSync"] = std::make_unique<GUI::DropDown>(
		sf::Vector2f(positionX, positionY + (offsetY * 2)),                                   //Dropdown Position
		sf::Vector2f(sizeX, sizeY),                                                           //Dropdown Size
		this->gameDetails->font,                                                              //Dropdown Text Font
		characterSize,                                                                        //Dropdown Text Character Size
		vSyncStringVector,																	  //Dropdown String Vector
		this->inputTime,                                                                      //Input Time
		this->maxInputTime,                                                                   //Max Input Time
		static_cast<unsigned>(vSyncStringVector.size())                                       //Size of String Vector
		);

	std::vector<std::string> antiAliasingStringVector{ "x0", "x1", "x2", "x4","x8", "x16", "x32"};
	this->dropdownMap["Anti-Aliasing"] = std::make_unique<GUI::DropDown>(
		sf::Vector2f(positionX, positionY + (offsetY * 3)),                                   //Dropdown Position
		sf::Vector2f(sizeX, sizeY),                                                           //Dropdown Size
		this->gameDetails->font,                                                              //Dropdown Text Font
		characterSize,                                                                        //Dropdown Text Character Size
		antiAliasingStringVector,														      //Dropdown String Vector
		this->inputTime,                                                                      //Input Time
		this->maxInputTime,                                                                   //Max Input Time
		static_cast<unsigned>(antiAliasingStringVector.size())                                //Size of String Vector
		);
}

/*Constructor & Destructor*/
Settings::Settings(GameDetails* game_details)
	: State(game_details)
{
	this->initVariables();
	this->initBackground();
	this->initTitles();
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
void Settings::renderBackground(sf::RenderTarget& target)
{
	target.draw(this->background);
}
void Settings::renderTitles(sf::RenderTarget& target)
{
	target.draw(this->titles);
}
void Settings::renderDropdowns(sf::RenderTarget& target)
{
	this->dropdownMap["Anti-Aliasing"]->render(target);
	this->dropdownMap["VSync"]->render(target);
	this->dropdownMap["Fullscreen"]->render(target);
	this->dropdownMap["Resolution"]->render(target);
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
	this->renderBackground(*target);

	/*Titles*/
	this->renderTitles(*target);

	/*Dropdowns*/
	this->renderDropdowns(*target);

	/*Buttons*/
	this->renderButtonMap(*target);
}
