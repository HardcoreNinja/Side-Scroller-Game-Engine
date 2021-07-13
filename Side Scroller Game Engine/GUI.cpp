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
	sf::Color outline_click_color,
	short id
)
{
	/*Button & Text Colors*/
	this->buttonIdleColor = button_idle_color;
	this->buttonHoverColor = button_hover_color;
	this->buttonClickColor = button_click_color;

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textClickColor = text_click_color;

	this->outlineIdleColor = sf::Color::White;
	this->outlineHoverColor = outline_hover_color;
	this->outlineClickColor = outline_click_color;

	/*Button Shape*/
	this->buttonShape.setPosition(button_shape_position);
	this->buttonShape.setSize(button_shape_size);
	this->buttonShape.setOrigin(this->buttonShape.getGlobalBounds().width / 2.f, this->buttonShape.getGlobalBounds().height / 2.f);
	this->buttonShape.setFillColor(this->buttonIdleColor);
	this->buttonShape.setOutlineColor(this->outlineIdleColor);
	this->buttonShape.setOutlineThickness(1.f);

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
	sf::Color outline_click_color,
	short id
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
		outline_click_color,
		id
	);
}
GUI::Button::~Button()
{
}

/*Getters*/
const bool GUI::Button::getButtonClickState() const
{
	if (this->buttonState == ButtonState::Click)
		return true;

	return false;
}
const short GUI::Button::getID() const
{
	return this->id;
}
const std::string GUI::Button::getString() const
{
	return this->text.getString();
}

/*Setters*/
void GUI::Button::setID(const short id)
{
	this->id = id;
}
void GUI::Button::setString(std::string string)
{
	this->text.setString(string);
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

/*DropDown========================================================================================================================================================================*/
/*Initializers*/
void GUI::DropDown::initVariables(
	sf::Vector2f dropdown_position, 
	sf::Vector2f dropdown_size, 
	sf::Font* font, 
	unsigned character_size, 
	std::string list[], 
	float input_time, 
	float max_input_time, 
	unsigned number_of_elements, 
	unsigned default_index
)
{
	this->activeElement = std::make_unique<GUI::Button>(
		dropdown_position,
		dropdown_size,
		font,
		list[default_index],
		character_size,
		sf::Color::White,
		sf::Color::Blue,
		sf::Color::Red
		);

	for (size_t i = 0; i < number_of_elements; i++)
		this->buttonVector.push_back(std::make_unique<GUI::Button>(
			sf::Vector2f(dropdown_position.x, dropdown_position.y + ((i + 1) * dropdown_size.y)),
			dropdown_size,
			font,
			list[i],
			character_size,
			sf::Color::White, sf::Color::Blue, sf::Color::Red,
			sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
			sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
			i
			)
		);
}

/*Constructor & Destructor*/
GUI::DropDown::DropDown(
	sf::Vector2f dropdown_position, 
	sf::Vector2f dropdown_size, 
	sf::Font* font, 
	unsigned character_size, 
	std::string list[], 
	float input_time, 
	float max_input_time, 
	unsigned number_of_elements, 
	unsigned default_index
) : inputTime(input_time), maxInputTime(max_input_time), show(false)
{
	this->initVariables(
		dropdown_position,
		dropdown_size,
		font,
		character_size,
		list,
		input_time,
		max_input_time,
		number_of_elements,
		default_index
	);
}
GUI::DropDown::~DropDown()
{
}

/*Getters*/
bool GUI::DropDown::getInputTime()
{
	if (this->inputTime >= this->maxInputTime)
	{
		this->inputTime = 0.f;
		return true;
	}

	return false;
}

/*Update Functions*/
void GUI::DropDown::updateInputTime(const float& dt)
{
	if (this->inputTime < this->maxInputTime)
		this->inputTime += 95.93f * dt;

	std::cout << "Input Time: " << this->inputTime << '\n';
}
void GUI::DropDown::update(sf::Vector2i mouse_window_position, const float& dt)
{
	this->updateInputTime(dt);

	this->activeElement->update(mouse_window_position);

	if (this->activeElement->getButtonClickState() && this->getInputTime())
	{
		if (this->show)
			this->show = false;
		else if (!this->show)
			this->show = true;
	}

	if (this->show)
	{
		for (auto& i : this->buttonVector)
		{
			i->update(mouse_window_position);

			if (i->getButtonClickState() && this->getInputTime())
			{
				this->show = false; 
				this->activeElement->setID(i->getID());
				this->activeElement->setString(i->getString());
			}
		}
	}
}

/*Render Functions*/
void GUI::DropDown::render(sf::RenderTarget& target)
{
	this->activeElement->render(target);

	if (this->show)
	{
		for (auto& i : this->buttonVector)
			i->render(target);
	}
}