#include "Header.h"
#include "State.h"

/*Initializers*/
void State::initVariables(GameDetails* game_details)
{
	this->gameDetails = game_details;
	this->endState = false;
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
bool State::getEndState()
{
	return this->endState;
}

/*Setters*/
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

