#ifndef GAME_H
#define GAME_H
class Game
{
private:

	std::unique_ptr<sf::RenderWindow> window;

	float dt; 
	sf::Clock dtClock;

	/*Initializers*/
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
