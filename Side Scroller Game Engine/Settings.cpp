#include "Header.h"
#include "Settings.h"

/*Initializers*/
void Settings::initVariables()
{
	this->videoModes = sf::VideoMode::getFullscreenModes();
	this->openFullscreenDropdown = true;
	this->openVSyncDropdown = true;
	this->openAntiAliasingDropdown = true;

	this->loadIDFromFile();
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
	float offsetX = 125.f;
	float offsetY = 50.f;

	float sizeX = 100.f;
	float sizeY = 25.f;

	unsigned characterSize = 10;

	/*Back*/
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

	/*Apply*/
	this->button = std::make_unique<GUI::Button>(
		sf::Vector2f(positionX + offsetX, positionY - offsetY), //Button Position
		sf::Vector2f(sizeX, sizeY),                             //Button Size
		this->gameDetails->font,                                //Text Font
		"apply",                                                //String                     
		characterSize,                                          //Character Size 
		sf::Color::White,                                       //Text Idle Color
		sf::Color::Blue,                                        //Text Hover Color
		sf::Color::Red                                          //Text Click Color
		);

	this->buttonMap["Apply"] = std::move(this->button);
}
void Settings::initDropDowns()
{
	float positionX = 350.f;
	float positionY = 85.f;
	float offsetY = 45;

	float sizeX = 100.f;
	float sizeY = 25.f;
	
	unsigned characterSize = 10;

	/*Resolution*/
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
	this->dropdownMap["Resolution"]->setActiveElementID(this->resolutionID);

	/*Fullscreen*/
	std::vector<std::string> fullscreenStringVector { "no", "yes" };
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
	this->dropdownMap["Fullscreen"]->setActiveElementID(this->fullscreenID);

	/*VSync*/
	std::vector<std::string> vSyncStringVector{ "no", "yes" };
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
	this->dropdownMap["VSync"]->setActiveElementID(this->vSyncID);

	/*Anti-Aliasing*/
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
	this->dropdownMap["Anti-Aliasing"]->setActiveElementID(this->antiAliasingID);
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

/*Setters*/
void Settings::setInitializers()
{
	this->initVariables();
	this->initBackground();
	this->initTitles();
	this->initButtons();
	this->initDropDowns();
}

/*Update Functions*/
void Settings::updateDropdowns(const float& dt)
{
	/*Resolution*/
	this->dropdownMap["Resolution"]->update(this->mousePositionWindow, dt);

	if (this->dropdownMap["Resolution"]->getShow())
	{
		this->openFullscreenDropdown = false;
		this->openVSyncDropdown = false;
		this->openAntiAliasingDropdown = false;
	}
	else if (!this->dropdownMap["Resolution"]->getShow() && this->gameDetails->event->type == sf::Event::MouseButtonReleased)
	{
		this->openFullscreenDropdown = true;
		this->openVSyncDropdown = true;
		this->openAntiAliasingDropdown = true;
	}

	/*Fullscreen*/
	if (this->openFullscreenDropdown)
	{
		this->dropdownMap["Fullscreen"]->update(this->mousePositionWindow, dt);

		if (this->dropdownMap["Fullscreen"]->getShow())
			this->openVSyncDropdown = false;
		else if (!this->dropdownMap["Fullscreen"]->getShow() && this->gameDetails->event->type == sf::Event::MouseButtonReleased)
			this->openVSyncDropdown = true;
	}

	/*VSync*/
	if (this->openVSyncDropdown)
	{
		this->dropdownMap["VSync"]->update(this->mousePositionWindow, dt);

		if (this->dropdownMap["VSync"]->getShow())
			this->openAntiAliasingDropdown = false;
		else if (!this->dropdownMap["VSync"]->getShow() && this->gameDetails->event->type == sf::Event::MouseButtonReleased)
			this->openAntiAliasingDropdown = true;
	}

	/*Anti-Aliasing*/
	if (this->openAntiAliasingDropdown)
		this->dropdownMap["Anti-Aliasing"]->update(this->mousePositionWindow, dt);
}
void Settings::updateButtons()
{
	/*Back*/
	if (this->buttonMap["Back"]->getButtonClickState() && this->getInputTime())
		this->setEndStateTrue();

	if (this->buttonMap["Apply"]->getButtonClickState() && this->getInputTime())
	{
		/*Resolution*/
	
		this->resolutionID = this->dropdownMap["Resolution"]->getActiveElementID();
		std::cout << "Resolution ID " << this->resolutionID << '\n';
		this->gameDetails->graphicsSettings->setVideoMode(this->videoModes[this->resolutionID]);

		/*Fullscreen*/
	
		this->fullscreenID = this->dropdownMap["Fullscreen"]->getActiveElementID();
		std::cout << "Fullscreen ID " << this->fullscreenID << '\n';
		this->gameDetails->graphicsSettings->setFullscreen(this->fullscreenID);

		/*VSync*/
		this->vSyncID = this->dropdownMap["VSync"]->getActiveElementID();
			std::cout << "VSync ID " << this->vSyncID << '\n';
		this->gameDetails->graphicsSettings->setVSync(this->vSyncID);

		/*Anti-Aliasing*/
		this->antiAliasingID = this->dropdownMap["Anti-Aliasing"]->getActiveElementID();
		std::cout << "AA ID " << this->antiAliasingID << '\n';

		switch (this->antiAliasingID)
		{
		case 0:
			this->gameDetails->graphicsSettings->setAntiAliasingLevel(0);
			break;
		case 1:
			this->gameDetails->graphicsSettings->setAntiAliasingLevel(1);
			break;
		case 2:
			this->gameDetails->graphicsSettings->setAntiAliasingLevel(2);
			break;
		case 3:
			this->gameDetails->graphicsSettings->setAntiAliasingLevel(4);
			break;
		case 4:
			this->gameDetails->graphicsSettings->setAntiAliasingLevel(8);
			break;
		case 5:
			this->gameDetails->graphicsSettings->setAntiAliasingLevel(16);
			break;
		case 6:
			this->gameDetails->graphicsSettings->setAntiAliasingLevel(32);
			break;
		default:
			throw ("ERROR::SETTINGS::INVAILD_SWITCH_ENTRY::void Settings::updateButtons()");
				break;
		}

		this->gameDetails->graphicsSettings->saveToFile();
		this->saveIDToFile();
		this->setWindow();
		this->setStateInitializations();
	}
}
void Settings::update(const float& dt)
{
	this->updateInputTime(dt);
	this->updateMousePosition();

	this->updateDropdowns(dt);
	this->updateButtonMap();
	this->updateButtons();	
}

/*Save & Load Active Element IDs*/
void Settings::saveIDToFile()
{
	std::ofstream ofs("Config/active_element_id.ini");

	if (ofs.is_open())
	{
		ofs << this->resolutionID << '\n';
		ofs << this->fullscreenID << '\n';
		ofs << this->vSyncID << '\n';
		ofs << this->antiAliasingID << '\n';
	}

	ofs.close();
}
void Settings::loadIDFromFile()
{
	std::ifstream ifs("Config/active_element_id.ini");

	if (ifs.is_open())
	{
		ifs >> this->resolutionID;
		ifs >> this->fullscreenID;
		ifs >> this->vSyncID;
		ifs >> this->antiAliasingID;
	}

	ifs.close();
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