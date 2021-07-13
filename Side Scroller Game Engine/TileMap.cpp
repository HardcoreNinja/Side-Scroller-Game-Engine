#include "Header.h"
#include "TileMap.h"
/*Tile========================================================================================================================================================================*/
/*Initializers*/
void TILEMAP::Tile::initVariables(
	const sf::Vector2f tile_position, 
	const sf::Texture& tile_texture,
	const sf::IntRect& tile_int_rect,
	short unsigned tile_rotation,
	const std::string door_name, 
	const TILEMAP::TileType tile_type

)
{
	this->tileSprite.setPosition(std::floor(tile_position.x), std::floor(tile_position.y));
	this->tileSprite.setTexture(tile_texture);
	this->tileSprite.setTextureRect(tile_int_rect);
	this->tileSprite.setRotation(tile_rotation);
	this->doorName = door_name;
	this->tileType = tile_type;
}

/*Constructor & Destructor*/
TILEMAP::Tile::Tile( 
	const sf::Vector2f tile_position, 
	const sf::Texture& tile_texture,
	const sf::IntRect& tile_int_rect,
	const short unsigned tile_rotation,
	const std::string door_name, 
	const TILEMAP::TileType tile_type

)
{
	this->initVariables(
		tile_position,
		tile_texture,
		tile_int_rect,
		tile_rotation,
		door_name,
		tile_type
	);
}
TILEMAP::Tile::~Tile()
{
}

/*Getters*/
const sf::Sprite TILEMAP::Tile::getTileSprite() const
{
	return this->tileSprite;
}
const sf::Vector2f TILEMAP::Tile::getTilePosition() const
{
	return this->tileSprite.getPosition();
}
const std::string TILEMAP::Tile::getDoorName() const
{
	return this->doorName;
}
const TILEMAP::TileType TILEMAP::Tile::getTileType() const
{
	return this->tileType;
}
const std::string TILEMAP::Tile::getTileMapInfo() const
{
	std::stringstream ss; 

	ss << this->tileSprite.getTextureRect().width << " " << this->tileSprite.getTextureRect().top << " "
		<< static_cast<int>(this->tileType) << " "
		<< this->doorName << " "
		<< this->tileRotation;

	return ss.str();
}

/*Render Functions*/
void TILEMAP::Tile::render(sf::RenderTarget& target)
{
	target.draw(this->tileSprite);
}

/*Tile Map========================================================================================================================================================================*/

/*Initializers*/
void TILEMAP::TileMap::initVariables(
	float tile_size, 
	sf::Vector2u map_size, 
	std::string file_path 
)
{
	this->tileSize = tile_size;
	this->mapSize = map_size;
	this->filePath = file_path;
	if (!this->texture.loadFromFile(this->filePath))
		throw ("ERROR::TILEMAP::TILEMAP::FAILED_TO_LOAD::THIS->FILEPATH");
	this->textureIntRect = sf::IntRect(0, 0, static_cast<int>(tile_size), static_cast<int>(tile_size));
	this->tileLayers = 10;

	this->tileMap.resize(this->tileLayers);
	for (size_t tile_layer = 0; tile_layer < this->tileLayers; tile_layer++)
	{
		this->tileMap[tile_layer].resize(this->mapSize.x);
		for (size_t x = 0; x < this->mapSize.x; x++)
			this->tileMap[tile_layer][x].resize(this->mapSize.y);
	}
}

/*Constructor & Destructor*/
TILEMAP::TileMap::TileMap(
	float tile_size,  
	sf::Vector2u map_size, 
	std::string file_path 
)
{
	this->initVariables(
		tile_size,
		map_size,
		file_path
	);
}
TILEMAP::TileMap::~TileMap()
{
}

void TILEMAP::TileMap::addTile(
	const unsigned tile_layer, 
	const sf::Vector2u tile_position, 
	const unsigned tile_rotation, 
	const std::string door_name, 
	const TILEMAP::TileType tile_type
)
{
	if (
		tile_layer < this->tileLayers && tile_layer >= 0 &&
		tile_position.x < this->mapSize.x && tile_position.x >= 0 &&
		tile_position.y < this->mapSize.y && tile_position.y >= 0

		)
	{
		if (this->tileMap[tile_layer][tile_position.x][tile_position.y] == NULL)
		{
			this->tileMap[tile_layer][tile_position.x][tile_position.y] = std::make_unique<TILEMAP::Tile>(
				sf::Vector2f(std::floor(static_cast<float>(tile_position.x)), std::floor(static_cast<float>(tile_position.y))),
				this->texture,
				sf::IntRect(this->textureIntRect.width, this->textureIntRect.height, static_cast<int>(std::floor(this->tileSize)), static_cast<int>(std::floor(this->tileSize))),
				tile_rotation,
				door_name,
				tile_type
				);
		}
	}
}
void TILEMAP::TileMap::removeTile(const unsigned tile_layer, const sf::Vector2u tile_position)
{
	if (
		tile_layer < this->tileLayers && tile_layer >= 0 &&
		tile_position.x < this->mapSize.x && tile_position.x >= 0 &&
		tile_position.y < this->mapSize.y && tile_position.y >= 0

		)
	{
		if (this->tileMap[tile_layer][tile_position.x][tile_position.y] != NULL)
		{
			this->tileMap[tile_layer][tile_position.x][tile_position.y].reset();
		}
	}
}
