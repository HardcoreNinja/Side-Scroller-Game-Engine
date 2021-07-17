#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#include "State.h"
#include "Settings.h"
#include "Editor.h"

/*Class Forward Declarations*/
class State;
class Settings;
class Editor;
class sf::Keyboard;
class sf::Mouse;
class sf::Event;
class GUI::Button;
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
    void initKeyBinds();
    void initButtons();
public: 
    /*Constructor & Destructor*/
    MainMenu(GameDetails* game_details);
    virtual ~MainMenu();

    /*Setters*/
    void setInitializers();

    /*Update Functions*/
    void updateUserInput();
    void updateButtons();
    void update(const float& dt);

    /*Render Functions*/
    void renderButtonMap(sf::RenderTarget& target);
    void render(sf::RenderTarget* target);
};
#endif
