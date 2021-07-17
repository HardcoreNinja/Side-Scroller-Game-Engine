#include "Header.h"
#include "PauseMenu.h"

/*Initializers*/
void PauseMenu::initBackground(sf::RenderWindow& window)
{
	/*Background*/
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x),
			static_cast<float>(window.getSize().y)
		)
	);
	this->background.setFillColor(sf::Color(0, 0, 0, 100));

	/*Button Container*/
	this->buttonContainer.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x) / 4.f,
			static_cast<float>(window.getSize().y)
		)
	);
	this->buttonContainer.setOrigin(
		this->buttonContainer.getGlobalBounds().width / 2.f, 
		this->buttonContainer.getGlobalBounds().height / 2.f
	); 
	this->buttonContainer.setPosition(
		static_cast<float>(window.getSize().x) / 2.f, this->buttonContainer.getSize().y / 2.f);
	this->buttonContainer.setFillColor(sf::Color(128, 128, 128, 100));
}
void PauseMenu::initText(sf::RenderWindow& window)
{
	this->textRect.setSize(sf::Vector2f(200.f, 50.f));
	this->textRect.setOrigin(this->textRect.getGlobalBounds().width / 2.f, this->textRect.getGlobalBounds().height / 2.f);
	this->textRect.setPosition(static_cast<float>(window.getSize().x) / 2.f, 30.f);

	this->text.setFont(this->font);
	this->text.setString("Pause Menu"); 
	this->text.setCharacterSize(20);
	this->text.setOrigin(this->text.getGlobalBounds().width / 2.f, this->text.getGlobalBounds().height / 2.f);
	this->text.setFillColor(sf::Color::White); 
	this->text.setPosition(this->textRect.getPosition().x, this->textRect.getPosition().y - static_cast<float>(this->text.getCharacterSize()) / 4.f);
}

/*Constructor & Destructor*/
PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font)
	: font(font)
{
	this->initBackground(window);
	this->initText(window);
}
PauseMenu::~PauseMenu()
{
}

/*Setters*/
void PauseMenu::setButton(std::string key, float offset, std::string name)
{
	float sizeX = 200.f; 
	float sizeY = 100.f;

	unsigned characterSize = 20;

	this->button = std::make_unique<GUI::Button>(
		sf::Vector2f(this->buttonContainer.getPosition().x, this->buttonContainer.getPosition().y + offset), //Button Position
		sf::Vector2f(sizeX, sizeY),                                 //Button Size
		&this->font,                                                 //Text Font
		name,                                                       //String
		characterSize,                                              //Character Size
		sf::Color::Blue, sf::Color::White, sf::Color::Red           //Text Color (Idle, Hover, Click)
		);
		
	this->buttonMap[key] = std::move(this->button);
}

/*Getters*/
const bool PauseMenu::getButtonClickState(std::string key)
{
	return this->buttonMap[key]->getButtonClickState();
}

/*Update Functions*/
void PauseMenu::update(const sf::Vector2i mouse_window_positon)
{
	for (auto& i : this->buttonMap)
		i.second->update(mouse_window_positon);

	this->text.setPosition(this->textRect.getPosition());
}

/*Render Functions*/
void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->buttonContainer);
	target.draw(this->text);

	for (auto& i : this->buttonMap)
		i.second->render(target);
}