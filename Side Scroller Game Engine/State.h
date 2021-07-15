#ifndef STATE_H
#define STATE_H
#include "GraphicsSettings.h"
#include "GUI.h"
#include "TileMap.h"

/*Class Forward Declarations*/
class State;
class GraphicsSettings;
class GUI::Button;
class GUI::DropDown;
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
	sf::Event* event;
	sf::Font* font;
};

class State
{
private:
	/*Initializers*/
	void initVariables(GameDetails* game_details);
	void initView();
protected:
	/*Game Detials*/
	GameDetails* gameDetails;

	/*Tile Map*/
	std::unique_ptr<TILEMAP::TileMap> tileMap;

	/*Background Variables*/
	sf::RectangleShape background; 
	sf::Texture backgroundTexture;

	/*User Input Variables*/
	sf::Vector2i mousePositionDesktop;
	sf::Vector2i mousePositionWindow; 
	sf::Vector2f mousePositionView; 
	sf::Vector2f mousePositionGUI;
	sf::Vector2u mousePositionTile;

	/*View*/
	sf::View view;

	/*Tile Size*/	

	unsigned tileSize;

	/*Buttons*/
	std::unique_ptr<GUI::Button> button; 
	std::map<std::string, std::unique_ptr<GUI::Button>> buttonMap;

	/*DropDowns*/
	std::unique_ptr<GUI::DropDown> dropdown; 
	std::map<std::string, std::unique_ptr<GUI::DropDown>> dropdownMap;

	/*Key Binds*/
	std::map<std::string, int> keyBindMap;

	/*Input Time*/
	float inputTime;
	float maxInputTime; 

	/*End State Bool*/
	bool endState;

public:
	/*Constructor & Destructor*/
	State(GameDetails* game_details);
	virtual ~State();

	/*Getters*/
	bool getInputTime();
	bool getEndState();

	/*Setters*/
	void setEndStateTrue();
	void setWindow();
	void setStateInitializations();
	virtual void setInitializers() = 0;

	/*Update Functions*/
	void updateResize();
	void updateMousePosition();
	void updateButtonMap();
	void updateInputTime(const float& dt);
	virtual void update(const float& dt) = 0;

	/*Render Functions*/
	virtual void render(sf::RenderTarget* target = NULL) = 0;
};
#endif
