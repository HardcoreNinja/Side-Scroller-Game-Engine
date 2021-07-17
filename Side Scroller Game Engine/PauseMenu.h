#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H
#include "GUI.h"

/*Class Forward Declarations*/
class Button;
class sf::RectangleShape;
class sf::Font;
class sf::Text;
class sf::RenderWindow;
class sf::Color;
class sf::RenderTarget;
class sf::RenderTarget;

class PauseMenu
{
private:
	/*Background Variables*/
	sf::RectangleShape background;
	sf::RectangleShape buttonContainer;

	/*Text Variables*/
	sf::Font& font; 
	sf::Text text;
	sf::RectangleShape textRect;

	/*Button Map Variables*/
	std::unique_ptr<GUI::Button> button;
	std::map<std::string, std::unique_ptr<GUI::Button>> buttonMap;

	/*Initializers*/
	void initBackground(sf::RenderWindow& window);
	void initText(sf::RenderWindow& window);
public:
	/*Constructor & Destructor*/
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~PauseMenu();

	/*Setters*/
	void setButton(std::string key, float offset, std::string name);

	/*Getters*/
	const bool getButtonClickState(std::string key);

	/*Update Functions*/
	void update(const sf::Vector2i mouse_window_positon);

	/*Render Functions*/
	void render(sf::RenderTarget& target);
};
#endif
