#include "Header.h"
#include "State.h"

/*Initializers*/
void State::initVariables(GameDetails* game_details)
{
	this->gameDetails = game_details;
	this->endState = false;
	this->inputTime = 0.f;
	this->maxInputTime = 100.f;
}

/*Constructor & Destructor*/
State::State(GameDetails* game_details)
{
	this->initVariables(game_details);
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
void State::setEndStateTrue()
{
	this->endState = true;
}

/*Update Functions*/
void State::updateMousePosition()
{
	this->mousePositionDesktop = sf::Mouse::getPosition();
	this->mousePositionWindow = sf::Mouse::getPosition(*this->gameDetails->window);
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