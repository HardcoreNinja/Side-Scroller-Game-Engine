#ifndef TILE_MAP_H
#define TILE_MAP_H

namespace TILEMAP
{
	enum class TileType
	{
		Default = 0,
		Wall = 1,
		Door = 2, 
		Entity_Spawn_Position = 3,
		Player_Enter_Position = 4,
		Path_Finding = 5, 
		Invisible_Wall = 6
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
		const std::string getTileMapInfo() const; 

		/*Render Functions*/
		void render(sf::RenderTarget& target);	
	};

	class TileMap
	{
	private: 
		float tileSize;
		unsigned tileLayers;
		sf::Vector2u mapSize;
		std::vector<std::vector<std::vector<std::unique_ptr<TILEMAP::Tile>>>> tileMap;
		std::string filePath;
		sf::Texture texture;
		sf::IntRect textureIntRect;

		/*Initializers*/
		void initVariables(
			float tile_size,
			sf::Vector2u map_size,
			std::string file_path
		);
	public: 
		/*Constructor & Destructor*/
		TileMap(
			float tile_size,
			sf::Vector2u map_size,
			std::string file_path
		);
		virtual ~TileMap();

		/*Add & Remove Tile Functions*/
		void addTile(
			const unsigned tile_layer,
			const sf::Vector2u tile_position,
			const unsigned tile_rotation,
			const std::string door_name,
			const TILEMAP::TileType tile_type
		);
		void removeTile(const unsigned tile_layer, const sf::Vector2u tile_position);
	};
}
#endif
