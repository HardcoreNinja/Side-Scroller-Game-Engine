#ifndef SETTINGS_H
#define SETTINGS_H
#include "State.h"

class Settings :
    public State
{
private:
    /*Initializers*/
    void initBackground();
    void initButtons();
public:
    /*Constructor & Destructor*/
    Settings(GameDetails* game_details);
    virtual ~Settings();

    /*Update Functions*/
    void updateButtons();
    void update(const float& dt);

    /*Render Functions*/
    void renderButtonMap(sf::RenderTarget& target);
    void render(sf::RenderTarget* target);
};
#endif
