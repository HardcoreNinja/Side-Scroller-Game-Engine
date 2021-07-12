#ifndef GAME_H
#define GAME_H
#include "MainMenu.h"

/*Class Forward Declarations*/
class MainMenu; 
class State;
class GraphicsSettings;
class sf::RenderWindow;
class sf::Clock;
class sf::Color;

class Game
{
private:
	/*Game Details*/
	GameDetails gameDetails; 

	/*States*/
	std::vector<std::unique_ptr<State>> states;

	/*Supported Keys*/
	std::map<std::string, int> supportedKeys;

	/*Graphics Settings*/
	std::unique_ptr<GraphicsSettings> graphicsSettings;

	/*Window*/
	std::unique_ptr<sf::RenderWindow> window;

	/*Delta Time Variables*/
	float dt; 
	sf::Clock dtClock;

	/*Initializers*/
	void initSupportedKey();
	void initGraphicsSettings();
	void initWindow();
	void initGameDetails();
	void initStates();

public:
	/*Constructor & Destructor*/
	Game();
	virtual ~Game();

	/*Update Functions*/
	void updateDeltaTime();
	void update();

	/*Render Functions*/
	void render();

	/*Run Function*/
	void run();
};
#endif
