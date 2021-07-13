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

		short id;

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
			sf::Color outline_click_color = sf::Color::Transparent,
			short id = 0
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
			sf::Color outline_click_color = sf::Color::Transparent,
			short id = 0
			);
		virtual ~Button();

		/*Getters*/
		const bool getButtonClickState() const;
		const short getID() const;
		const std::string getString() const;


		/*Setters*/
		void setID(const short id);
		void setString(std::string string);

		/*Update Functions*/
		void updateButtonState(const sf::Vector2i& mouse_window_position);
		void update(const sf::Vector2i& mouse_window_position);

		/*Render Functions*/
		void render(sf::RenderTarget& target);
	};

	class DropDown
	{
	private:
		std::unique_ptr<GUI::Button> activeElement;

		std::vector<std::unique_ptr<GUI::Button>> buttonVector;

		sf::Font* font;

		float inputTime; 
		float maxInputTime; 

		bool show;

		/*Initializers*/
		void initVariables(
			sf::Vector2f dropdown_position,
			sf::Vector2f dropdown_size,
			sf::Font* font,
			unsigned character_size,
			std::string list[],
			float input_time,
			float max_input_time,
			unsigned number_of_elements,
			unsigned default_index = 0
		);
	public: 
		/*Constructor & Destructor*/
		DropDown(
			sf::Vector2f dropdown_position,
			sf::Vector2f dropdown_size,
			sf::Font* font, 
			unsigned character_size, 
			std::string list[],
			float input_time, 
			float max_input_time, 
			unsigned number_of_elements, 
			unsigned default_index = 0
			);
		virtual ~DropDown();

		/*Getters*/
		bool getInputTime();


		/*Update Functions*/
		void updateInputTime(const float& dt);
		void update(sf::Vector2i mouse_window_position, const float& dt);

		/*Render Functions*/
		void render(sf::RenderTarget& target);

	};
}
#endif
