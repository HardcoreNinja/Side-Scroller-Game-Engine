#ifndef STATE_H
#define STATE_H
#include "GraphicsSettings.h"

/*Class Forward Declarations*/
class State;
class GraphicsSettings;
class sf::RenderTarget;
class sf::RenderWindow;
class sf::RectangleShape;
class sf::Texture;
class sf::Color;

struct GameDetails
{
	GameDetails(std::map<std::string, int>& supported_keys)
		: supportedKeys(supported_keys)
	{
	}

	std::map<std::string, int>& supportedKeys; 

	GraphicsSettings* graphicsSettings; 
	sf::RenderWindow* window;
	std::vector<std::unique_ptr<State>>* states;
};

class State
{
private:
	/*Initializers*/
	void initVariables(GameDetails* game_details);
protected:
	/*Game Detials*/
	GameDetails* gameDetails;

	/*Background Variables*/
	sf::RectangleShape background; 
	sf::Texture backgroundTexture; 
public:
	/*Constructor & Destructor*/
	State(GameDetails* game_details);
	virtual ~State();

	/*Update Functions*/
	virtual void update(const float& dt) = 0;

	/*Render Functions*/
	virtual void render(sf::RenderTarget* target = NULL) = 0;
};
#endif
