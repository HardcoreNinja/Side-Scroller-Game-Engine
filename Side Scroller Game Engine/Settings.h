#ifndef SETTINGS_H
#define SETTINGS_H
#include "State.h"

class Settings :
    public State
{
private:
    sf::Text titles;

    std::vector<sf::VideoMode> videoModes;

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

    /*Update Functions*/
    void updateDropdowns(const float& dt);
    void updateButtons();
    void update(const float& dt);

    /*Render Functions*/
    void renderBackground(sf::RenderTarget& target);
    void renderTitles(sf::RenderTarget& target);
    void renderDropdowns(sf::RenderTarget& target);
    void renderButtonMap(sf::RenderTarget& target);
    void render(sf::RenderTarget* target);
};
#endif
