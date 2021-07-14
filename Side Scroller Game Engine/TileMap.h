#ifndef TILE_MAP_H
#define TILE_MAP_H
#include "GUI.h"

namespace TILEMAP
{
	enum class TileType
	{
		Default = 0,
		Wall = 1,
		Invisible_Wall = 2,
		Door = 3, 
		Entity_Spawn_Position = 4,
		Player_Enter_Position = 5,
		Path_Marker = 6
	};

	class Tile
	{
	private: 

		sf::Sprite tileSprite;
		std::string doorName;
		TileType tileType;
		short unsigned tileRotation;
	
		/*Initializers*/
		void initVariables(
			const sf::Vector2f tile_position,
			const sf::Texture& tile_texture,
			const sf::IntRect& tile_int_rect,
			const short unsigned tile_rotation = 0,
			const std::string door_name = "NULL",
			const TILEMAP::TileType tile_type = TileType::Default
		
		);
	public:
		/*Constructor & Destructor*/
		Tile(
			const sf::Vector2f tile_position,
			const sf::Texture& tile_texture,
			const sf::IntRect& tile_int_rect,
			short unsigned tile_rotation = 0,
			const std::string door_name = "NULL",
			const TILEMAP::TileType tile_type = TileType::Default
		);
		virtual ~Tile();

		/*Getters*/
		const sf::Sprite getTileSprite() const;
		const sf::Vector2f getTilePosition() const; 
		const std::string getDoorName() const; 
		const TILEMAP::TileType getTileType() const;
		const std::string getInfoAsString() const; 

		/*Render Functions*/
		void render(sf::RenderTarget& target);	
	};

	class TileMap
	{
	private: 
		unsigned tileSize;
		unsigned tileLayers;
		sf::Vector2u mapSize;
		std::vector<std::vector<std::vector<std::unique_ptr<TILEMAP::Tile>>>> tileMap;
		std::string filePath;
		sf::Texture texture;
		sf::IntRect textureIntRect;

		/*Initializers*/
		void initVariables(
			unsigned tile_size,
			sf::Vector2u map_size,
			std::string file_path
		);
	public: 
		/*Constructor & Destructor*/
		TileMap(
			unsigned tile_size,
			sf::Vector2u map_size,
			std::string file_path
		);
		virtual ~TileMap();

		/*Getters*/
		const sf::Texture getTexture();
		const sf::IntRect getTextureIntRect();

		/*Setters*/
		void setTextureIntRect(sf::IntRect texture_int_rect);
		void setTileSize(unsigned tile_size);

		/*Double & Halve Tile Functions*/
		void doubleTileSize();
		void halveTileSize();

		/*Add & Remove Tile Functions*/
		void addTile(
			const unsigned tile_layer,
			const sf::Vector2u tile_position,
			const unsigned tile_rotation,
			const std::string door_name,
			const TILEMAP::TileType tile_type
		);
		void removeTile(const unsigned tile_layer, const sf::Vector2u tile_position);

		/*Clear Function*/
		void clear();

		/*Save & Load Functions*/
		void saveToFile();
		void loadFromFile();

		/*Render Functions*/
		void render(sf::RenderTarget& target, sf::View& view);
	};

	class TextureSelector
	{
	private:
		
		sf::RectangleShape bounds;
		sf::Sprite textureSheet; 
		sf::IntRect textureIntRect; 
		sf::Vector2u mousePositionTile;
		sf::RectangleShape selector;

		unsigned tileSize; 

		std::unique_ptr<GUI::Button> hideButton; 

		bool show; 
		bool active; 

		float inputTime; 
		float maxInputTime; 

		int xScrollIncrementer; 
		int yScrollIncrementer;

		/*Initializers*/
		void initVariables(
			std::string data_file_path,
			sf::Vector2f bounds_position,
			sf::Vector2f bounds_size,
			const sf::Texture* texture_sheet, 
			sf::Font* font
		);
	public:
		/*Constructor & Destructor*/
		TextureSelector(
			std::string data_file_path,
			unsigned tileSize,
			sf::Vector2f bounds_position,
			sf::Vector2f bounds_size,
			const sf::Texture* texture_sheet,
			sf::Font* font,
			float input_time,
			float max_input_time
		);
		virtual ~TextureSelector();

		/*Getters*/
		const sf::IntRect getTextureIntRect();
		const bool getActive(); 
		const bool getInputTime();

		/*Update Functions*/
		void updateInputTime(const float& dt);
		void update(const sf::Vector2i mouse_position_window, const float& dt);

		/*Scroll Functions*/
		void scrollUp();
		void scrollDown();
		void scrollLeft();
		void scrollRight();

		/*Double & Halve Selector Functions*/
		void doubleSelectorSize();
		void halveSelectorSize();

		/*Save & Load Functions*/
		void saveToFile();
		void loadFromFile();

		/*Render Functions*/
		void render(sf::RenderTarget& target, const sf::View& view);

	};
}
#endif
