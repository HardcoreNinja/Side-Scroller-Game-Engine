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
void MainMenu::initKeyBinds()
{
	std::ifstream ifs("Config/main_menu_key_binds.ini");

	std::string keyBindKey = "";
	std::string supportedKeysKey = "";

	if (ifs.is_open())
	{
		while (ifs >> keyBindKey >> supportedKeysKey)
			this->keyBindMap[keyBindKey] = this->gameDetails->supportedKeys[supportedKeysKey];	
	}

	ifs.close();
}
void MainMenu::initButtons()
{
	float positionX = 125.f;
	float positionY = static_cast<float>(this->gameDetails->window->getSize().y) / 2.f;
	float offsetX = 125.f;
	float offsetY = 150.f;

	float sizeX = 200.f;
	float sizeY = 100.f;

	unsigned characterSize = 20;

	/*Settings*/
	this->button = std::make_unique<GUI::Button>(
		sf::Vector2f(positionX + (offsetX * 0), positionY + (offsetY * 0)), //Button Position
		sf::Vector2f(sizeX, sizeY),											//Button Size
		this->gameDetails->font,											//Text Font
		"settings",                                                         //String                     
		characterSize,                                                      //Character Size 
		sf::Color::White,                                                   //Text Idle Color
		sf::Color::Blue,                                                    //Text Hover Color
		sf::Color::Red                                                      //Text Click Color
		);

	this->buttonMap["Settings"] = std::move(this->button);

	/*Editor*/
	this->button = std::make_unique<GUI::Button>(
		sf::Vector2f(positionX + (offsetX * 0), positionY - (offsetY * 1)), //Button Position
		sf::Vector2f(sizeX, sizeY),											//Button Size
		this->gameDetails->font,											//Text Font
		"editor",															//String                     
		characterSize,                                                      //Character Size 
		sf::Color::White,                                                   //Text Idle Color
		sf::Color::Blue,                                                    //Text Hover Color
		sf::Color::Red                                                      //Text Click Color
		);

	this->buttonMap["Editor"] = std::move(this->button);

	/*Quit Game*/
	this->button = std::make_unique<GUI::Button>(
		sf::Vector2f(positionX + (offsetX * 0), positionY + (offsetY * 1)), //Button Position
		sf::Vector2f(sizeX, sizeY),											//Button Size
		this->gameDetails->font,											//Text Font
		"quit game",                                                        //String                     
		characterSize,                                                      //Character Size 
		sf::Color::White,                                                   //Text Idle Color
		sf::Color::Blue,                                                    //Text Hover Color
		sf::Color::Red                                                      //Text Click Color
		);

	this->buttonMap["Quit_Game"] = std::move(this->button);
}

/*Constructor & Destructor*/
MainMenu::MainMenu(GameDetails* game_details)
	: State(game_details)
{
	this->initBackground();
	this->initKeyBinds();
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
void MainMenu::updateUserInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBindMap["Quit_Game"])) && this->getInputTime())
		this->setEndStateTrue();
}
void MainMenu::updateButtons()
{
	if (this->buttonMap["Editor"]->getButtonClickState() && this->getInputTime())
		this->gameDetails->states->push_back(std::make_unique<Editor>(this->gameDetails));

	if (this->buttonMap["Settings"]->getButtonClickState() && this->getInputTime())
		this->gameDetails->states->push_back(std::make_unique<Settings>(this->gameDetails));

	if (this->buttonMap["Quit_Game"]->getButtonClickState() && this->getInputTime())
		this->setEndStateTrue();
}
void MainMenu::update(const float& dt)
{
	if (this->gameDetails->event->type == sf::Event::Resized)
		this->updateResize();
	this->updateMousePosition();
	this->updateButtonMap();

	this->updateUserInput();
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