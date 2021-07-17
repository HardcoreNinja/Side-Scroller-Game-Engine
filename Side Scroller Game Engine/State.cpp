#include "Header.h"
#include "State.h"

/*Initializers*/
void State::initVariables(GameDetails* game_details)
{
	this->gameDetails = game_details;
	this->pauseGame = false;
	this->tileSize = 64;
	this->endState = false;
	this->inputTime = 0.f;
	this->maxInputTime = 100.f;
}
void State::initView()
{
	this->view.setSize(static_cast<float>(this->gameDetails->window->getSize().x), static_cast<float>(this->gameDetails->window->getSize().y));
	this->view.setCenter(static_cast<float>(this->gameDetails->window->getSize().x) / 2.f, static_cast<float>(this->gameDetails->window->getSize().y) / 2.f);
}

/*Constructor & Destructor*/
State::State(GameDetails* game_details)
{
	this->initVariables(game_details);
	this->initView();
}
State::~State()
{
}

/*Getters*/
bool State::getInputTime()
{
	if (this->inputTime >= this->maxInputTime)
	{
		this->inputTime = 0.f; 
		return true;
	}

	return false;
}
bool State::getEndState()
{
	return this->endState;
}

/*Setters*/
void State::setPauseGame()
{
	if (this->pauseGame)
		this->pauseGame = false;
	else if (!this->pauseGame)
		this->pauseGame = true;
}
void State::setEndStateTrue()
{
	this->endState = true;
}
void State::setWindow()
{
	auto style = this->gameDetails->graphicsSettings->getFullScreen() ? sf::Style::Fullscreen : sf::Style::Default;

	this->gameDetails->window->create(
		this->gameDetails->graphicsSettings->getVideoMode(),
		this->gameDetails->graphicsSettings->getTitle(),
		style,
		this->gameDetails->graphicsSettings->getContextSettings()
		);

	this->gameDetails->window->setVerticalSyncEnabled(this->gameDetails->graphicsSettings->getVSync());
	this->gameDetails->window->setFramerateLimit(this->gameDetails->graphicsSettings->getFrameRateLimit());
}
void State::setStateInitializations()
{
	for (auto& i : *this->gameDetails->states)
		i->setInitializers();
}

/*Update Functions*/
void State::updateResize()
{
	float aspectRatio = static_cast<float>(this->gameDetails->window->getSize().x) / static_cast<float>(this->gameDetails->window->getSize().y);

	this->view.setSize(static_cast<float>(this->gameDetails->window->getSize().x) * aspectRatio, static_cast<float>(this->gameDetails->window->getSize().y) * aspectRatio);
	this->view.setCenter((static_cast<float>(this->gameDetails->window->getSize().x) * aspectRatio) / 2.f, (static_cast<float>(this->gameDetails->window->getSize().y) * aspectRatio) / 2.f);

	this->gameDetails->graphicsSettings->setVideoMode(sf::VideoMode(this->gameDetails->window->getSize().x, this->gameDetails->window->getSize().y));
	this->gameDetails->graphicsSettings->saveToFile();
	this->setWindow();
	this->setStateInitializations();
	this->initView();
}
void State::updateMousePosition()
{
	/*Desktop*/
	this->mousePositionDesktop = sf::Mouse::getPosition();

	/*Window*/
	this->mousePositionWindow = sf::Mouse::getPosition(*this->gameDetails->window);

	/*View*/
	this->gameDetails->window->setView(this->view);
	this->mousePositionView = this->gameDetails->window->mapPixelToCoords(sf::Mouse::getPosition(*this->gameDetails->window));

	/*Tile w/ View*/
	this->mousePositionTile = sf::Vector2u(
		static_cast<unsigned>(this->mousePositionView.x) / this->tileSize,
		static_cast<unsigned>(this->mousePositionView.y) / this->tileSize
	);

	/*GUI*/
	this->gameDetails->window->setView(this->gameDetails->window->getDefaultView());
	this->mousePositionGUI = this->gameDetails->window->mapPixelToCoords(sf::Mouse::getPosition(*this->gameDetails->window));
}
void State::updateButtonMap()
{
	for (auto& i : this->buttonMap)
		i.second->update(this->mousePositionWindow);
}
void State::updateInputTime(const float& dt)
{
	if (this->inputTime < this->maxInputTime)
		this->inputTime += 95.93f * dt;

	//std::cout << "Input Time: " << this->inputTime << '\n';
}