#ifndef GAME_H
#define GAME_H
#include "GraphicsSettings.h"

/*Class Forward Declarations*/
class GraphicsSettings;
class sf::RenderWindow;
class sf::Clock;
class sf::Color;

class Game
{
private:
	/*Graphics Settings*/
	std::unique_ptr<GraphicsSettings> graphicsSettings;

	/*Window*/
	std::unique_ptr<sf::RenderWindow> window;

	/*Delta Time Variables*/
	float dt; 
	sf::Clock dtClock;

	/*Initializers*/
	void initGraphicsSettings();
	void initWindow();
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
