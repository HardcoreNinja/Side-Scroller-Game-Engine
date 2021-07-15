#ifndef EDITOR_H
#define EDITOR_H
#include "State.h"
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

    /*View Variables*/
    float cameraSpeed; 

    /*Cursor Text*/
    sf::Text cursorText;

    /*Initializers*/
    void initVariables();
    void initKeyBinds();
    void initText();
    void initTileMap();
    void initTextureSelector();
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
    void updateUserInput();
    void update(const float& dt);

    /*Render Functions*/
    void renderTextureSelector(sf::RenderTarget& target);
    void renderSelectorRect(sf::RenderTarget& target);
    void renderCursorText(sf::RenderTarget& target);
    void renderTileMap(sf::RenderTarget& target);
    void render(sf::RenderTarget* target);
};
#endif
