#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#include "State.h"

/*Class Forward Declarations*/
class State;
class GraphicsSettings;
class sf::RenderTarget;
class sf::RectangleShape; 
class sf::Texture;
class sf::Color;

class MainMenu :
    public State
{
private:
    /*Initializers*/
    void initBackground();
public: 
    /*Constructor & Destructor*/
    MainMenu(GameDetails* game_details);
    virtual ~MainMenu();

    /*Update Functions*/
    void update(const float& dt);

    /*Render Functions*/
    void render(sf::RenderTarget* target);
};
#endif
