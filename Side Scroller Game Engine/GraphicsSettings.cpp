#include "Header.h"
#include "GraphicsSettings.h"

/*Initializers*/
void GraphicsSettings::initVariables()
{
	this->title = "Default Title";
	this->videoMode = sf::VideoMode(800, 600);
	this->fullScreen = false;
	this->vSync = false; 
	this->frameRateLimit = 120;
	this->contextSettings.antialiasingLevel = 0;
}

/*Constructor & Destructor*/
GraphicsSettings::GraphicsSettings()
{
	this->initVariables();
}
GraphicsSettings::~GraphicsSettings()
{
}

/*Getters*/
const std::string GraphicsSettings::getTitle()
{
	return this->title;
}
const sf::VideoMode GraphicsSettings::getVideoMode()
{
	return this->videoMode;
}
const bool GraphicsSettings::getFullScreen()
{
	return this->fullScreen;
}
const bool GraphicsSettings::getVSync()
{
	return this->vSync;
}
const unsigned int GraphicsSettings::getFrameRateLimit()
{
	return this->frameRateLimit;
}
const sf::ContextSettings GraphicsSettings::getContextSettings()
{
	return this->contextSettings;
}

/*Save & Load Functions*/
void GraphicsSettings::saveToFile()
{
	std::ofstream ofs("Config/graphics_settings.ini");

	if (ofs.is_open())
	{
		ofs << this->title << '\n';
		ofs << this->videoMode.width << " " << this->videoMode.height << '\n';
		ofs << this->fullScreen << '\n';
		ofs << this->vSync << '\n';
		ofs << this->frameRateLimit << '\n';
		ofs << this->contextSettings.antialiasingLevel << '\n';
	}
	ofs.close();
}
void GraphicsSettings::loadFromFile()
{
	std::ifstream ifs("Config/graphics_settings.ini");

	if (ifs.is_open())
	{
		std::getline(ifs, this->title);
		ifs >> this->videoMode.width >> this->videoMode.height;
		ifs >> this->fullScreen; 
		ifs >> this->vSync;
		ifs >> this->frameRateLimit;
		ifs >> this->contextSettings.antialiasingLevel;
	}
	ifs.close();
}
