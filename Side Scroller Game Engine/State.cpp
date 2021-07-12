#include "Header.h"
#include "State.h"

/*Initializers*/
void State::initVariables(GameDetails* game_details)
{
	this->gameDetails = game_details;
}

/*Constructor & Destructor*/
State::State(GameDetails* game_details)
{
	this->initVariables(game_details);
}
State::~State()
{
}
