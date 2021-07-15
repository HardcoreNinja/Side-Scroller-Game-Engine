#include "Header.h"
#include "Editor.h"

/*Initializers*/
void Editor::initVariables()
{
	/*Tile Variables*/
	this->tileRotation = 0;
	this->maxTileRotation = 270;
	this->doorName = "NULL";
	this->tileType = 0;
	this->maxTileType = 6;

	/*Tile Map Variables*/
	this->tileLayer = 0; 
	this->maxTileLayer = 10; 

	/*View Variables*/
	this->cameraSpeed = 1280.f;
}
void Editor::initKeyBinds()
{
	std::ifstream ifs("Config/editor_keybinds.ini");

	std::string keyBindKey = "";
	std::string supportedKeysKey = "";

	if (ifs.is_open())
	{
		while (ifs >> keyBindKey >> supportedKeysKey)
			this->keyBindMap[keyBindKey] = this->gameDetails->supportedKeys[supportedKeysKey];
	}

	ifs.close();
}
void Editor::initText()
{
	this->cursorText.setFont(*this->gameDetails->font);
	this->cursorText.setCharacterSize(10);
	this->cursorText.setFillColor(sf::Color::White);
}
void Editor::initTileMap()
{
	unsigned tileSize = 0;
	sf::Vector2u mapSize = sf::Vector2u(0, 0);
	

	std::ifstream ifs("Config/tile_map.ini");

	if (ifs.is_open())
	{
		ifs >> tileSize;
		ifs >> mapSize.x >> mapSize.y;
	}
	else
		throw ("ERROR::EDITOR::void Editor::initTileMap()::FAILED_TO_LOAD::tile_map.ini");

	ifs.close(); 

	this->tileMap = std::make_unique<TILEMAP::TileMap>(
		tileSize,
		mapSize,
		"Resources/Images/Texture_Sheets/PipoyaMasterLevel.png"
		);
}
void Editor::initTextureSelector()
{
	unsigned tileSize = 0;

	std::ifstream ifs("Config/tile_map.ini");

	if (ifs.is_open())
	{
		ifs >> tileSize;
	}
	else
		throw ("ERROR::EDITOR::void Editor::initTextureSelector()::FAILED_TO_LOAD::tile_map.ini");

	ifs.close();

	this->textureSelector = std::make_unique<TILEMAP::TextureSelector>(
		"Config/texture_selector_data.ini",
		tileSize,
		sf::Vector2f(0, 0),
		sf::Vector2f(256.f, 512.f),
		this->tileMap->getTexture(),
		this->gameDetails->font,
		this->inputTime,
		this->maxInputTime
		);

	this->selectorRect.setSize(sf::Vector2f(static_cast<float>(tileSize), static_cast<float>(tileSize)));
	//this->selectorRect.setFillColor(sf::Color::Transparent);
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Green);
	this->selectorRect.setTextureRect(this->tileMap->getTextureIntRect());
	this->selectorRect.setTexture(this->tileMap->getTexture());
}
void Editor::initLoadLatestTileMap()
{
	this->tileMap->loadFromFile();
}

/*Constructor & Destructor*/
Editor::Editor(GameDetails* game_details)
	: State(game_details)
{
	this->initVariables();
	this->initKeyBinds();
	this->initText();
	this->initTileMap();
	this->initTextureSelector();
	this->initLoadLatestTileMap();
}
Editor::~Editor()
{
}

/*Setters*/
void Editor::setInitializers()
{
	//this->tileMap->saveToFile();
	this->initVariables(); 
	this->initKeyBinds(); 
	this->initText();
	this->initTileMap();
	this->initTextureSelector();
	this->initLoadLatestTileMap();
}

/*Update Functions*/
void Editor::updateTileRotation()
{
	if (this->tileRotation < this->maxTileRotation)
		this->tileRotation += 90;
	else if (this->tileRotation == this->maxTileRotation)
		this->tileRotation = 0;
}
void Editor::updateTileType()
{
	if (this->tileType < this->maxTileType)
		this->tileType += 1;
	else if (this->tileType == this->maxTileType)
		this->tileType = 0;
}
void Editor::updateTileLayer()
{
	if (this->tileLayer < this->maxTileLayer)
		this->tileLayer += 1;
	else if (this->tileLayer == this->maxTileLayer)
		this->tileLayer = 0;
}
void Editor::updateCursorText()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBindMap["Backspace"])) && this->getInputTime())
	{
		if (this->doorName.size() > 0)
			this->doorName.pop_back();
	}

	if (
		this->gameDetails->event->type == sf::Event::TextEntered
		&& sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBindMap["Left_Shift"]))
		&& this->getInputTime()
		)
	{
		if (
			this->gameDetails->event->text.unicode < 128
			&& this->gameDetails->event->text.unicode != 8
			&& this->gameDetails->event->text.unicode != 27
			&& this->doorName.size() <= 20
			)
		{
			this->doorName.push_back(static_cast<char>(this->gameDetails->event->text.unicode));
		}
	}

		this->cursorText.setPosition(static_cast<float>(this->mousePositionWindow.x) + 100.f, static_cast<float>(this->mousePositionWindow.y) - 50.f);

		std::stringstream ss; 

		ss << "mouse position window: " << this->mousePositionWindow.x << " x " << this->mousePositionWindow.y << '\n'
			<< "mouse position view: " << this->mousePositionView.x << " x " << this->mousePositionView.y << '\n'
			<< " mouse position tile: " << this->mousePositionTile.x << " x " << this->mousePositionTile.y << '\n'
			<< "tile map int rect: " << this->tileMap->getTextureIntRect().left << " x " << this->tileMap->getTextureIntRect().top << '\n'
			<< "tile rotation: " << this->tileRotation << '\n'
			<< "door name: " << this->doorName << '\n'
			<< "tile type: " << this->tileType << '\n'
			<< "tile layer: " << this->tileLayer;

		this->cursorText.setString(ss.str());
}
void Editor::updateSelectorRect()
{
	if (!this->textureSelector->getActive())
	{
		this->selectorRect.setTexture(this->tileMap->getTexture());
		this->selectorRect.setTextureRect(this->tileMap->getTextureIntRect());
		this->selectorRect.setRotation(this->tileRotation);

		this->selectorRect.setPosition(sf::Vector2f(
			static_cast<float>(this->mousePositionTile.x * this->tileSize),
			static_cast<float>(this->mousePositionTile.y * this->tileSize)
		)
		);
	}
}
void Editor::updateTextureSelector(const float& dt)
{
	this->textureSelector->update(this->mousePositionGUI, dt);
}
void Editor::updateTileMap()
{
	/*Add Tile*/
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!this->textureSelector->getActive())
		{
			this->tileMap->addTile(
				this->tileLayer,
				this->mousePositionTile,
				this->tileRotation,
				this->doorName,
				static_cast<TILEMAP::TileType>(this->tileType)
			);
		}
		else if (this->textureSelector->getActive())
			this->tileMap->setTextureIntRect(this->textureSelector->getTextureIntRect());
	}

	/*Remove Tile*/
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		this->tileMap->removeTile(this->tileLayer, this->mousePositionTile);
}
void Editor::updateUserInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBindMap["Back_To_Main_Menu"])) && this->getInputTime())
	{
		this->tileMap->saveToFile();
		this->setEndStateTrue();
	}
}
void Editor::update(const float& dt)
{
	if (this->gameDetails->event->type == sf::Event::Resized)
		this->updateResize();

	this->updateMousePosition();
	this->updateButtonMap();
	this->updateInputTime(dt); 

	this->updateCursorText();
	this->updateTextureSelector(dt);
	this->updateTileMap();
	this->updateSelectorRect();
	this->updateUserInput();
}

/*Render Functions*/
void Editor::renderTextureSelector(sf::RenderTarget& target)
{
	this->textureSelector->render(target, this->gameDetails->window->getDefaultView());
}
void Editor::renderSelectorRect(sf::RenderTarget& target)
{
	target.draw(this->selectorRect);
}
void Editor::renderCursorText(sf::RenderTarget& target)
{
	target.draw(this->cursorText);
}
void Editor::renderTileMap(sf::RenderTarget& target)
{
	this->tileMap->render(target, this->view);
}
void Editor::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->gameDetails->window;

	
	this->renderSelectorRect(*target);
	this->renderCursorText(*target);
	this->renderTileMap(*target);
	this->renderTextureSelector(*target);
}