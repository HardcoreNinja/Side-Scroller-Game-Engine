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
	this->maxTileLayer = 4; 

	/*View Variables*/
	this->cameraSpeed = 1280.f;
}
void Editor::initPauseMenu()
{
	this->pauseMenu = std::make_unique<PauseMenu>(
		*this->gameDetails->window,
		*this->gameDetails->font
		);

	/*Buttons*/
	float offsetY = 100.f;

	this->pauseMenu->setButton("Save", -offsetY, "Save");
	this->pauseMenu->setButton("Load", 0, "Load");
	this->pauseMenu->setButton("Quit", offsetY * 2, "Quit");
}
void Editor::initBackground()
{
	this->environmentDetails.background.setSize(
		sf::Vector2f(
			static_cast<float>(this->gameDetails->window->getSize().x * 2),
			static_cast<float>(this->gameDetails->window->getSize().y)
		)
	);

	if (!this->environmentDetails.backgroundTexture.loadFromFile("Resources/Images/Background/Level_1/background.png"))
		throw ("ERROR::EDITOR::FAILED_TO_LOAD::background.png");

	this->environmentDetails.backgroundTexture.setRepeated(true);
	this->environmentDetails.backgroundTexture.setSmooth(true);

	this->environmentDetails.background.setTextureRect(
		sf::IntRect(
			0, 
			0, 
			this->environmentDetails.background.getSize().x,
			this->environmentDetails.background.getSize().y
		)
	);

	this->environmentDetails.background.setTexture(&this->environmentDetails.backgroundTexture);
}
void Editor::initForeground()
{
	this->environmentDetails.foreground.setSize(
		sf::Vector2f(
			static_cast<float>(this->gameDetails->window->getSize().x * 2),
			static_cast<float>(this->gameDetails->window->getSize().y)
		)
	);

	if (!this->environmentDetails.foregroundTexture.loadFromFile("Resources/Images/Foreground/foreground.png"))
		throw ("ERROR::EDITOR::FAILED_TO_LOAD::background.png");

	this->environmentDetails.foregroundTexture.setRepeated(true);
	this->environmentDetails.foregroundTexture.setSmooth(true);

	this->environmentDetails.foreground.setTextureRect(
		sf::IntRect(
			0,
			0,
			this->environmentDetails.foreground.getSize().x,
			this->environmentDetails.foreground.getSize().y
		)
	);

	this->environmentDetails.foreground.setTexture(&this->environmentDetails.foregroundTexture);
}
void Editor::initRenderTexture()
{
	this->renderTexture.create(this->gameDetails->window->getSize().x, this->gameDetails->window->getSize().y);
	this->renderTexture.setSmooth(true);
	
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(sf::IntRect( 0, 0, this->gameDetails->window->getSize().x, this->gameDetails->window->getSize().y));
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
	sf::Vector2u mapSize = sf::Vector2u(0, 0);
	std::ifstream ifs("Config/tile_map.ini");

	if (ifs.is_open())
	{
		ifs >> mapSize.x >> mapSize.y;
	}
	else
		throw ("ERROR::EDITOR::void Editor::initTileMap()::FAILED_TO_LOAD::tile_map.ini");

	ifs.close(); 

	this->tileMap = std::make_unique<TILEMAP::TileMap>(
		this->tileSize,
		mapSize,
		"Resources/Images/Tile_Set/tileset.png"
		);
}
void Editor::initTextureSelector()
{
	this->textureSelector = std::make_unique<TILEMAP::TextureSelector>(
		"Config/texture_selector_data.ini", //Texture Selector Data File
		this->tileSize,                     //Tile Size
		sf::Vector2f(0, 0),                 //Bounds Position
		sf::Vector2f(768.f, 384.f),         //Bounds Size
		this->tileMap->getTexture(),        //Texture
		this->gameDetails->font,            //Font
		this->inputTime,                    //Input Time
		this->maxInputTime                  //Max Input Time
		);

	this->selectorRect.setSize(sf::Vector2f(static_cast<float>(this->tileSize), static_cast<float>(this->tileSize)));
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Green);
	this->selectorRect.setTextureRect(this->tileMap->getTextureIntRect());
	this->selectorRect.setTexture(this->tileMap->getTexture());
}
void Editor::initSideBar()
{
	this->sideBar.setSize(
		sf::Vector2f(
			static_cast<float>(this->tileSize),
			static_cast<float>(this->gameDetails->window->getSize().y)
		)
	);

	this->sideBar.setFillColor(sf::Color::Black);
	this->sideBar.setOutlineThickness(1.f);
	this->sideBar.setOutlineColor(sf::Color::White);
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
	this->initPauseMenu();
	this->initBackground();
	this->initForeground();
	this->initRenderTexture();
	this->initKeyBinds();
	this->initText();
	this->initTileMap();
	this->initTextureSelector();
	this->initSideBar();
	this->initLoadLatestTileMap();
}
Editor::~Editor()
{
}

/*Setters*/
void Editor::setInitializers()
{
	this->tileMap->saveToFile();
	this->initVariables(); 
	this->initRenderTexture();
	this->initKeyBinds(); 
	this->initText();
	this->initTileMap();
	this->initTextureSelector();
	this->initSideBar();
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

		ss << "mouse position window: " << this->mousePositionWindow.x << " x " << this->mousePositionWindow.y << "\n\n"
			<< "mouse position view: " << this->mousePositionView.x << " x " << this->mousePositionView.y << "\n\n"
			<< " mouse position tile: " << this->mousePositionTile.x << " x " << this->mousePositionTile.y << "\n\n"
			<< "tile map int rect: " << this->tileMap->getTextureIntRect().left << " x " << this->tileMap->getTextureIntRect().top << "\n\n"
			<< "tile rotation: " << this->tileRotation << "\n\n"
			<< "door name: " << this->doorName << "\n\n"
			<< "tile type: " << this->tileType << "\n\n"
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
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getInputTime())
	{
		if (!this->textureSelector->getActive() && !this->sideBar.getGlobalBounds().contains(static_cast<sf::Vector2f>(this->mousePositionWindow)))
		{
			this->tileMap->addTile(
				this->tileLayer,
				this->mousePositionTile,
				this->tileRotation,
				this->doorName,
				static_cast<TILEMAP::TileType>(this->tileType)
			);
		}
		else if (this->textureSelector->getActive() && !this->sideBar.getGlobalBounds().contains(static_cast<sf::Vector2f>(this->mousePositionWindow)))
			this->tileMap->setTextureIntRect(this->textureSelector->getTextureIntRect());
	}

	/*Remove Tile*/
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		this->tileMap->removeTile(this->tileLayer, this->mousePositionTile);
}
void Editor::updateUserInput(const float& dt)
{
	/*Back To Main Menu*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBindMap["Pause_Menu"])) && this->getInputTime())
		this->setPauseGame();
	
	if (this->pauseGame)
	{
		if (this->pauseMenu->getButtonClickState("Save"))
			this->tileMap->saveToFile();

		if (this->pauseMenu->getButtonClickState("Load"))
			this->tileMap->loadFromFile();

		if (this->pauseMenu->getButtonClickState("Quit"))
		{
			this->tileMap->saveToFile();
			this->tileSize = 64;
			this->setEndStateTrue();
		}
	}
	else if (!this->pauseGame)
	{
		/*Double Tile Size*/
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBindMap["Double_Tile_Size"])) && this->getInputTime())
		{
			this->tileSize = this->tileSize * 2;
			this->tileMap->doubleTileSize();
			this->textureSelector->doubleSelectorSize();
			this->tileMap->setTextureIntRect(this->textureSelector->getTextureIntRect());
			this->selectorRect.setSize(sf::Vector2f(this->textureSelector->getTextureIntRect().width, this->textureSelector->getTextureIntRect().height));
			this->selectorRect.setTextureRect(this->textureSelector->getTextureIntRect());
		}

		/*Halving Tile Size*/
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBindMap["Halve_Tile_Size"])) && this->getInputTime())
		{
			this->tileSize = this->tileSize / 2;
			this->tileMap->halveTileSize();
			this->textureSelector->halveSelectorSize();
			this->tileMap->setTextureIntRect(this->textureSelector->getTextureIntRect());
			this->selectorRect.setSize(sf::Vector2f(this->textureSelector->getTextureIntRect().width, this->textureSelector->getTextureIntRect().height));
			this->selectorRect.setTextureRect(this->textureSelector->getTextureIntRect());
		}

		/*Camera Controls*/
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBindMap["Camera_Up"])))
			this->view.move(0.f, -this->cameraSpeed * dt);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBindMap["Camera_Down"])))
			this->view.move(0.f, this->cameraSpeed * dt);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBindMap["Camera_Left"])))
			this->view.move(-this->cameraSpeed * dt, 0.f);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBindMap["Camera_Right"])))
			this->view.move(this->cameraSpeed * dt, 0.f);

		/*Update Rotation*/
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBindMap["Rotate_Tile"])) && this->getInputTime())
			this->updateTileRotation();

		/*Update Tile Type*/
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBindMap["Tile_Type"])) && this->getInputTime())
			this->updateTileType();

		/*Update Tile Layer*/
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBindMap["Tile_Layer"])) && this->getInputTime())
			this->updateTileLayer();

		/*Texture Sheet Scroll Up*/
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBindMap["Scroll_Up"])) && this->getInputTime())
			this->textureSelector->scrollUp();
		else if (this->gameDetails->event->type == sf::Event::MouseWheelScrolled && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBindMap["Left_Shift"])))
		{
			if (this->gameDetails->event->mouseWheelScroll.delta > 0)
			{
				this->textureSelector->scrollUp();
				this->gameDetails->event->mouseWheelScroll.delta = 0;
			}
		}

		/*Texture Sheet Scroll Down*/
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBindMap["Scroll_Down"])))
			this->textureSelector->scrollDown();
		else if (this->gameDetails->event->type == sf::Event::MouseWheelScrolled && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBindMap["Left_Shift"])))
		{
			if (this->gameDetails->event->mouseWheelScroll.delta < 0)
			{
				this->textureSelector->scrollDown();
				this->gameDetails->event->mouseWheelScroll.delta = 0;
			}
		}

		/*Texture Sheet Scroll Left*/
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBindMap["Scroll_Left"])))
			this->textureSelector->scrollLeft();
		else if (this->gameDetails->event->type == sf::Event::MouseWheelScrolled && sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBindMap["Left_Shift"])))
		{
			if (this->gameDetails->event->mouseWheelScroll.delta < 0)
			{
				this->textureSelector->scrollLeft();
				this->gameDetails->event->mouseWheelScroll.delta = 0;
			}
		}

		/*Texture Sheet Scroll Right*/
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBindMap["Scroll_Right"])))
			this->textureSelector->scrollRight();
		else if (this->gameDetails->event->type == sf::Event::MouseWheelScrolled && sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBindMap["Left_Shift"])))
		{
			if (this->gameDetails->event->mouseWheelScroll.delta > 0)
			{
				this->textureSelector->scrollRight();
				this->gameDetails->event->mouseWheelScroll.delta = 0;
			}
		}
	}
}
void Editor::update(const float& dt)
{
	if (this->gameDetails->event->type == sf::Event::Resized)
		this->updateResize();
	this->updateMousePosition();
	this->updateInputTime(dt);
	this->updateUserInput(dt);
	//this->updateButtonMap();
	
	if (this->pauseGame)
		this->pauseMenu->update(this->mousePositionWindow);
	else if (!this->pauseGame)
	{
		this->updateCursorText();
		this->updateTextureSelector(dt);
		this->updateTileMap();
		this->updateSelectorRect();
	}
}

/*Render Functions*/
void Editor::renderBackground(sf::RenderTarget& target)
{
	target.draw(this->environmentDetails.background);
}
void Editor::renderForeground(sf::RenderTarget& target)
{
	target.draw(this->environmentDetails.foreground);
}
void Editor::renderSideBar(sf::RenderTarget& target)
{
	target.draw(this->sideBar);
}
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

	/*Items to be Rendered With View*/
	this->renderTexture.clear();
	this->renderTexture.setView(this->view);
	this->renderBackground(this->renderTexture);
	this->renderTileMap(this->renderTexture);
	this->renderForeground(this->renderTexture);
	this->renderSelectorRect(this->renderTexture);
	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);

	/*Items to be Rendered With Window Default View*/
	target->setView(this->gameDetails->window->getDefaultView());
	this->renderSideBar(*target);
	this->renderTextureSelector(*target);
	this->renderCursorText(*target);
	if (this->pauseGame)
		this->pauseMenu->render(*target);
}