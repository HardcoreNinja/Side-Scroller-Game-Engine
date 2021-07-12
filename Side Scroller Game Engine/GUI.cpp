#include "Header.h"
#include "GUI.h"

/*Button========================================================================================================================================================================*/
/*Initializers*/
void GUI::Button::initVariables(
	sf::Vector2f button_shape_position,
	sf::Vector2f button_shape_size,
	sf::Font* font, 
	std::string string, 
	unsigned character_size, 
	sf::Color text_idle_color, 
	sf::Color text_hover_color, 
	sf::Color text_click_color, 
	sf::Color button_idle_color, 
	sf::Color button_hover_color, 
	sf::Color button_click_color, 
	sf::Color outline_idle_color, 
	sf::Color outline_hover_color, 
	sf::Color outline_click_color
)
{
	/*Button & Text Colors*/
	this->buttonIdleColor = button_idle_color;
	this->buttonHoverColor = button_hover_color;
	this->buttonClickColor = button_click_color;

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textClickColor = text_click_color;

	this->outlineIdleColor = outline_idle_color;
	this->outlineHoverColor = outline_hover_color;
	this->outlineClickColor = outline_click_color;

	/*Button Shape*/
	this->buttonShape.setPosition(button_shape_position);
	this->buttonShape.setSize(button_shape_size);
	this->buttonShape.setOrigin(this->buttonShape.getGlobalBounds().width / 2.f, this->buttonShape.getGlobalBounds().height / 2.f);
	this->buttonShape.setFillColor(this->buttonIdleColor);
	this->buttonShape.setOutlineColor(this->outlineIdleColor);

	/*Text Shape*/
	this->text.setFont(*font);
	this->text.setString(string);
	this->text.setCharacterSize(character_size);
	this->text.setOrigin(this->text.getGlobalBounds().width / 2.f, this->text.getGlobalBounds().height / 2.f);
	this->text.setPosition(this->buttonShape.getPosition().x, this->buttonShape.getPosition().y - static_cast<float>(this->text.getCharacterSize()) / 4.f);
	this->text.setFillColor(this->textIdleColor);
}

/*Constructor & Destructor*/
GUI::Button::Button(
	sf::Vector2f button_shape_position,
	sf::Vector2f button_shape_size,
	sf::Font* font, 
	std::string string, 
	unsigned character_size, 
	sf::Color text_idle_color, 
	sf::Color text_hover_color, 
	sf::Color text_click_color, 
	sf::Color button_idle_color, 
	sf::Color button_hover_color, 
	sf::Color button_click_color, 
	sf::Color outline_idle_color, 
	sf::Color outline_hover_color, 
	sf::Color outline_click_color
)
{
	this->initVariables(
		button_shape_position,
		button_shape_size,
		font,
		string,
		character_size,
		text_idle_color,
		text_hover_color,
		text_click_color,
		button_idle_color,
		button_hover_color,
		button_click_color,
		outline_idle_color,
		outline_hover_color,
		outline_click_color
	);
}
GUI::Button::~Button()
{
}

/*Getters*/
bool GUI::Button::getButtonClickState()
{
	if (this->buttonState == ButtonState::Click)
		return true;

	return false;
}

/*Update Functions*/
void GUI::Button::updateButtonState(const sf::Vector2i& mouse_window_position)
{
	if (!this->buttonShape.getGlobalBounds().contains(static_cast<float>(mouse_window_position.x), static_cast<float>(mouse_window_position.y)))
		this->buttonState = ButtonState::Idle;
	else if (this->buttonShape.getGlobalBounds().contains(static_cast<float>(mouse_window_position.x), static_cast<float>(mouse_window_position.y)))
	{
		this->buttonState = ButtonState::Hover;

		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			this->buttonState = ButtonState::Click;
	}

	switch (this->buttonState)
	{
	case ButtonState::Idle:
		this->buttonShape.setFillColor(this->buttonIdleColor);
		this->buttonShape.setOutlineColor(this->outlineIdleColor);
		this->text.setFillColor(this->textIdleColor);
		break;
	case ButtonState::Hover:
		this->buttonShape.setFillColor(this->buttonHoverColor);
		this->buttonShape.setOutlineColor(this->outlineHoverColor);
		this->text.setFillColor(this->textHoverColor);
		break;
	case ButtonState::Click:
		this->buttonShape.setFillColor(this->buttonClickColor);
		this->buttonShape.setOutlineColor(this->outlineClickColor);
		this->text.setFillColor(this->textClickColor);
		break;
	default:
		throw ("ERROR::GUI::BUTTON::INVALID_SWITCH_ENTRY::void GUI::Button::updateButtonState(sf::Vector2i mouse_window_position)");
		break;
	}

}
void GUI::Button::update(const sf::Vector2i& mouse_window_position)
{
	this->updateButtonState(mouse_window_position);
}

/*Render Functions*/
void GUI::Button::render(sf::RenderTarget& target)
{
	target.draw(this->buttonShape);
	target.draw(this->text);
}

