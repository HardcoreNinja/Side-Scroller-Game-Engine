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

	/*Color Codes*/
	switch (this->tileType)
	{
	case TILEMAP::TileType::Wall:
		this->tileSprite.setColor(sf::Color::Red);
		break;
	case TILEMAP::TileType::Invisible_Wall:
		this->tileSprite.setColor(sf::Color::Yellow);
		break;
	case TILEMAP::TileType::Door:
		this->tileSprite.setColor(sf::Color::Blue);
		break;
	case TILEMAP::TileType::Entity_Spawn_Position:
		this->tileSprite.setColor(sf::Color::White);
		break;
	case TILEMAP::TileType::Player_Enter_Position:
		this->tileSprite.setColor(sf::Color::Green);
		break;
	case TILEMAP::TileType::Path_Marker:
		this->tileSprite.setColor(sf::Color::Cyan);
		break;
	default: 
		throw("ERROR::TILEMAP::TILE::INVALID_SWITCH_ENTRY::void TILEMAP::Tile::initVariables()");
		break;
	}
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
const std::string TILEMAP::Tile::getInfoAsString() const
{
	std::stringstream ss; 

	ss << this->tileSprite.getTextureRect().width << " " << this->tileSprite.getTextureRect().top << " "
		<< this->tileRotation << " "
		<< this->doorName << " "
		<< static_cast<int>(this->tileType);
	
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
	unsigned tile_size,
	sf::Vector2u map_size, 
	std::string file_path 
)
{
	this->tileSize = tile_size;
	this->mapSize = map_size;
	this->filePath = file_path;
	if (!this->texture.loadFromFile(this->filePath))
		throw ("ERROR::TILEMAP::TILEMAP::FAILED_TO_LOAD::THIS->FILEPATH");
	this->textureIntRect = sf::IntRect(0, 0, tile_size, tile_size);
	this->tileLayers = 10;

	this->tileMap.resize(this->tileLayers);
	for (size_t tile_layer = 0; tile_layer < this->tileLayers; tile_layer++)
	{
		this->tileMap[tile_layer].resize(this->mapSize.x);
		for (size_t x_pos = 0; x_pos < this->mapSize.x; x_pos++)
			this->tileMap[tile_layer][x_pos].resize(this->mapSize.y);
	}
}

/*Constructor & Destructor*/
TILEMAP::TileMap::TileMap(
	unsigned tile_size,
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

/*Getters*/
const sf::Texture TILEMAP::TileMap::getTexture()
{
	return this->texture;
}
const sf::IntRect TILEMAP::TileMap::getTextureIntRect()
{
	return this->textureIntRect;
}

/*Setters*/
void TILEMAP::TileMap::setTextureIntRect(sf::IntRect texture_int_rect)
{
	this->textureIntRect = texture_int_rect;
}
void TILEMAP::TileMap::setTileSize(unsigned tile_size)
{
	this->tileSize = tile_size;
}

/*Double & Halve Tile Functions*/
void TILEMAP::TileMap::doubleTileSize()
{
	this->tileSize = this->tileSize * 2;
}
void TILEMAP::TileMap::halveTileSize()
{
	this->tileSize = this->tileSize / 2;
}

/*Add & Remove Tile Functions*/
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
				sf::IntRect(this->textureIntRect.width, this->textureIntRect.height, this->tileSize, this->tileSize),
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

/*Clear Function*/
void TILEMAP::TileMap::clear()
{
	for (size_t tile_layer = 0; tile_layer < this->tileLayers; tile_layer++)
	{
		for (size_t x_pos = 0; x_pos < this->tileLayers; x_pos++)
		{
			for (size_t y_pos = 0; y_pos < this->tileLayers; y_pos++)
				this->tileMap[tile_layer][x_pos][y_pos].reset();
			
			this->tileMap[tile_layer][x_pos].clear();
		}
		this->tileMap[tile_layer].clear();
	}
	this->tileMap.clear();
}

/*Save & Load Functions*/
void TILEMAP::TileMap::saveToFile()
{
	std::ofstream ofs("Config/tile_map.ini");

	if (ofs.is_open())
	{
		ofs << this->mapSize.x << " " << this->mapSize.y << '\n';
		ofs << static_cast<unsigned>(std::floor(this->tileSize)) << '\n';
		ofs << this->tileLayers << '\n';
		ofs << this->filePath << '\n';

		for (size_t tile_layer = 0; tile_layer < this->tileLayers; tile_layer)
		{
			for (size_t x_pos = 0; x_pos < this->tileLayers; x_pos)
			{
				for (size_t y_pos = 0; y_pos < this->tileLayers; y_pos++)
				{
					if (this->tileMap[tile_layer][x_pos][y_pos])
					{
						ofs << tile_layer << " "
							<< x_pos << " "
							<< y_pos << " "
							<< this->tileMap[tile_layer][x_pos][y_pos]->getInfoAsString() << " "
							<< static_cast<unsigned>(std::floor(this->tileSize)) << " ";
					}
				}
			}
		}
	}
	else
		throw ("ERROR::TILEMAP::TileMap::FAILED_TO_OPEN::SAVE_TO_FILE::tile_map.ini");

	ofs.close();

	std::cout << "Saved Tile Map!\n";
}
void TILEMAP::TileMap::loadFromFile()
{
	std::ifstream ifs("Config/tile_map.ini");

	if (ifs.is_open())
	{
		sf::Vector2u mapSize = sf::Vector2u(0, 0);
		unsigned tileSize = 0;
		unsigned tileLayers = 0;
		std::string filePath = "";
		sf::Vector2f tilePosition = sf::Vector2f(0.f, 0.f);
		unsigned intRectLeft;
		unsigned intRectTop;
		unsigned short tileRotation;
		std::string doorName;
		short tileType;
	
		ifs >> mapSize.x >> mapSize.y;
		ifs >> tileSize; 
		ifs >> tileLayers;
		ifs >> filePath; 

		this->mapSize.x = mapSize.x;
		this->mapSize.y = mapSize.y;
		this->tileSize = tileSize;
		this->tileLayers = tileLayers;
		this->filePath = filePath; 

		if (!this->texture.loadFromFile(this->filePath))
			throw("ERROR::TILEMAP::TileMap::void TILEMAP::TileMap::loadFromFile()::FAILED_TO_LOAD::this->filePath");

		this->clear();

		this->tileMap.resize(this->tileLayers);
		for (size_t tile_layer = 0; tile_layer < this->tileLayers; tile_layer++)
		{
			this->tileMap[tile_layer].resize(this->mapSize.x);
			for (size_t x_pos = 0; x_pos < this->mapSize.x; x_pos++)
				this->tileMap[tile_layer][x_pos].resize(this->mapSize.y);
		}

		while (ifs >> tileLayers >> tilePosition.x >> tilePosition.y >> intRectLeft >> intRectTop >> tileRotation >> doorName >> tileType >> tileSize)
			this->tileMap[tileLayers][tilePosition.x][tilePosition.y] = std::make_unique<TILEMAP::Tile>(
				tilePosition,
				this->filePath,
				sf::IntRect(intRectLeft, intRectTop, tileSize, tileSize),
				tileRotation,
				doorName,
				tileType
				);
	}
	else
		throw ("ERROR::TILEMAP::TileMap::FAILED_TO_OPEN::LOAD_FROM_FILE::tile_map.ini");

	ifs.close(); 

	std::cout << "Loaded Tile Map!\n";
}

/*Render Functions*/
void TILEMAP::TileMap::render(sf::RenderTarget& target, sf::View& view)
{
	float sizeOffset = 256.f;

	sf::Vector2f viewSize = view.getSize();
	viewSize.x = viewSize.x + sizeOffset;
	viewSize.y = viewSize.y + sizeOffset;

	sf::FloatRect viewRect(
		view.getCenter().x - viewSize.x / 2.f,
		view.getCenter().y - viewSize.y / 2.f,
		viewSize.x, viewSize.y
	);

	sf::FloatRect tileRect(
		0,
		0,
		static_cast<float>(this->tileSize),
		static_cast<float>(this->tileSize)
	);

	for (auto& tile_layer : this->tileMap)
	{
		for (auto& pos_x : tile_layer)
		{
			for (auto& pos_y : pos_x)
			{
				if (pos_y != NULL)
				{
					tileRect.left = pos_y->getTilePosition().x;
					tileRect.top = pos_y->getTilePosition().y;
					if (tileRect.intersects(viewRect))
						pos_y->render(target);
				}
			}
		}
	}
}
