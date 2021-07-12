#ifndef GUI_H
#define GUI_H

namespace GUI
{
	/*Class Forward Declarations*/
	class sf::Text;
	class sf::Color;
	class sf::RectangleShape;
	class sf::Font; 
	class sf::RenderTarget;

	/*Button State Enum*/
	enum class ButtonState
	{
		Idle = 0, 
		Hover = 1,
		Click = 2
	};
	class Button
	{
	private: 

		ButtonState buttonState;

		sf::Text text;
		sf::RectangleShape buttonShape;
		
		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textClickColor;

		sf::Color buttonIdleColor;
		sf::Color buttonHoverColor;
		sf::Color buttonClickColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineClickColor;

		/*Initializers*/
		void initVariables(
			sf::Vector2f button_shape_position,
			sf::Vector2f button_shape_size,
			sf::Font* font,
			std::string string,
			unsigned character_size,
			sf::Color text_idle_color,
			sf::Color text_hover_color,
			sf::Color text_click_color,
			sf::Color button_idle_color = sf::Color::Transparent,
			sf::Color button_hover_color = sf::Color::Transparent,
			sf::Color button_click_color = sf::Color::Transparent,
			sf::Color outline_idle_color = sf::Color::Transparent,
			sf::Color outline_hover_color = sf::Color::Transparent,
			sf::Color outline_click_color = sf::Color::Transparent
		);
	public:
		/*Constructor & Destructor*/
		Button(
			sf::Vector2f button_shape_position,
			sf::Vector2f button_size,
			sf::Font* font,
			std::string string,
			unsigned character_size,
			sf::Color text_idle_color,
			sf::Color text_hover_color,
			sf::Color text_click_color,
			sf::Color button_idle_color = sf::Color::Transparent,
			sf::Color button_hover_color = sf::Color::Transparent,
			sf::Color button_click_color = sf::Color::Transparent,
			sf::Color outline_idle_color = sf::Color::Transparent,
			sf::Color outline_hover_color = sf::Color::Transparent,
			sf::Color outline_click_color = sf::Color::Transparent
			);
		virtual ~Button();

		/*Getters*/
		bool getButtonClickState();

		/*Update Functions*/
		void updateButtonState(const sf::Vector2i& mouse_window_position);
		void update(const sf::Vector2i& mouse_window_position);

		/*Render Functions*/
		void render(sf::RenderTarget& target);
	};
}
#endif
