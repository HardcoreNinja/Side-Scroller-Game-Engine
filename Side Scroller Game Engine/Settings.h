#ifndef SETTINGS_H
#define SETTINGS_H
#include "State.h"

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
    void updateDropdowns(const float& dt);
    void updateButtons();
    void update(const float& dt);

    /*Save & Load Active Element IDs*/
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
