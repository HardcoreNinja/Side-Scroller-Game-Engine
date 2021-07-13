#ifndef GRAPHICS_SETTINGS_H
#define GRAPHICS_SETTINGS_H

/*Class Forward Declarations*/
class sf::VideoMode;

class GraphicsSettings
{
private: 
	/*Graphics Settings Variables*/
	std::string title;
	sf::VideoMode videoMode;
	bool fullScreen; 
	bool vSync;
	unsigned int frameRateLimit; 
	sf::ContextSettings contextSettings;

	/*Initializers*/
	void initVariables();
public:
	/*Constructor & Destructor*/
	GraphicsSettings();
	virtual ~GraphicsSettings();

	/*Getters*/
	const std::string getTitle(); 
	const sf::VideoMode getVideoMode(); 
	const bool getFullScreen();
	const bool getVSync(); 
	const unsigned int getFrameRateLimit();
	const sf::ContextSettings getContextSettings();

	/*Setters*/
	void setVideoMode(const sf::VideoMode video_mode);
	void setFullscreen(const bool full_screen);
	void setVSync(const bool vsync);
	void setAntiAliasingLevel(const unsigned int anti_aliasing_level);

	/*Save & Load Functions*/
	void saveToFile();
	void loadFromFile();
};
#endif
