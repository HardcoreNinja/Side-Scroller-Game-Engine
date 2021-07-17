#ifndef SETTINGS_H
#define SETTINGS_H
#include "State.h"

/*Class Forward Declarations*/
class State;
class GraphicsSettings;
class sf::Keyboard;
class sf::Mouse;
class sf::Event;
class GUI::Button;
class GUI::DropDown;
class sf::VideoMode;
class sf::RenderTarget;
class sf::RenderWindow;
class sf::RectangleShape;
class sf::Text;
class sf::Font;
class sf::Texture;
class sf::Color;
class sf::View;
class sf::Sprite;
class sf::RenderTexture;

class Settings :
    public State
{
private:
    sf::Text titles;

    std::vector<sf::VideoMode> videoModes;

    bool openFullscreenDropdown; 
    bool openVSyncDropdown;
    bool openAntiAliasingDropdown;

    short resolutionID; 
    short fullscreenID;
    short vSyncID;
    short antiAliasingID;

    /*Initializers*/
    void initVariables();
    void initBackground();
    void initKeyBinds();
    void initTitles();
    void initButtons();
    void initDropDowns();
public:
    /*Constructor & Destructor*/
    Settings(GameDetails* game_details);
    virtual ~Settings();

    /*Setters*/
    void setInitializers();

    /*Update Functions*/
    void updateUserInput();
    void updateDropdowns(const float& dt);
    void updateButtons();
    void update(const float& dt);

    /*Save & Load Functions*/
    void saveIDToFile();
    void loadIDFromFile();

    /*Render Functions*/
    void renderBackground(sf::RenderTarget& target);
    void renderTitles(sf::RenderTarget& target);
    void renderDropdowns(sf::RenderTarget& target);
    void renderButtonMap(sf::RenderTarget& target);
    void render(sf::RenderTarget* target);
};
#endif
