#ifndef EDITOR_H
#define EDITOR_H
#include "State.h"

/*Class Forward Declarations*/
class State;
class PauseMenu;
class GUI::Button;
class sf::Keyboard;
class sf::Mouse;
class sf::Event;
class sf::RenderTarget;
class sf::RectangleShape;
class sf::Text;
class sf::Texture;
class sf::Color;

class Editor :
    public State
{
private: 
    /*Tile Variables*/
    short unsigned tileRotation;
    short unsigned maxTileRotation;
    std::string doorName;
    short tileType;
    short maxTileType;

    /*Tile Map Variables*/
    unsigned tileLayer; 
    unsigned maxTileLayer; 

    /*Texture Selector*/
    std::unique_ptr<TILEMAP::TextureSelector> textureSelector;
    sf::RectangleShape selectorRect;

    /*Side Bar*/
    sf::RectangleShape sideBar;

    /*View Variables*/
    float cameraSpeed; 

    /*Cursor Text*/
    sf::Text cursorText;

    /*Initializers*/
    void initVariables();
    void initPauseMenu();
    void initBackground();
    void initForeground();
    void initRenderTexture();
    void initKeyBinds();
    void initText();
    void initTileMap();
    void initTextureSelector();
    void initSideBar();
    void initLoadLatestTileMap();
public:
    /*Constructor & Destructor*/
    Editor(GameDetails* game_details);
    virtual ~Editor();

    /*Setters*/
    void setInitializers();

    /*Update Functions*/
    void updateTileRotation();
    void updateTileType();
    void updateTileLayer();
    void updateCursorText();
    void updateSelectorRect();
    void updateTextureSelector(const float& dt);
    void updateTileMap();
    void updateUserInput(const float& dt);
    void update(const float& dt);

    /*Render Functions*/
    void renderBackground(sf::RenderTarget& target);
    void renderForeground(sf::RenderTarget& target);
    void renderSideBar(sf::RenderTarget& target);
    void renderTextureSelector(sf::RenderTarget& target);
    void renderSelectorRect(sf::RenderTarget& target);
    void renderCursorText(sf::RenderTarget& target);
    void renderTileMap(sf::RenderTarget& target);
    void render(sf::RenderTarget* target);
};
#endif
