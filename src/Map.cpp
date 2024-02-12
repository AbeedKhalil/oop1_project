#include "Map.h"

void Map::preloadTextures() {
	if (!wallTexture->loadFromFile("Wall.png")) {
		std::cerr << "Failed to load wall texture\n";
	}

	if (!mouseTexture->loadFromFile("Mouse.png")) {
		std::cerr << "Failed to load mouse texture\n";
	}
	if (!catTexture->loadFromFile("SmartCat.png")) {
		std::cerr << "Failed to load mouse texture\n";
	}
	if (!cheeseTexture->loadFromFile("Cheese.png")) {
		std::cerr << "Failed to load wall texture\n";
	}

	if (!doorTexture->loadFromFile("Door.png")) {
		std::cerr << "Failed to load mouse texture\n";
	}
	if (!keyTexture->loadFromFile("Key.png")) {
		std::cerr << "Failed to load wall texture\n";
	}

	if (!giftTexture->loadFromFile("GiftRemoveCat.png")) {
		std::cerr << "Failed to load mouse texture\n";
	}

	if (!tileTexture->loadFromFile("TileSheet.png")) {
		std::cerr << "Failed to load tile texture\n";
	}
}

Map::Map(unsigned width, unsigned height, sf::Texture* tileSheet, unsigned tileSize)
	: tileSheet(tileSheet), tileSize(tileSize), wallTexture(nullptr), mouseTexture(nullptr),
	catTexture(nullptr), cheeseTexture(nullptr), doorTexture(nullptr),
	keyTexture(nullptr), giftTexture(nullptr), tileTexture(nullptr)
{
	this->tiles.resize(width);
	for (size_t i = 0; i < this->tiles.size(); i++)
	{
		this->tiles[i].resize(height, nullptr);
	}
}

Map::~Map()
{
	for (int i = 0; i < this->tiles.size(); i++)
	{
		for (int j = 0; j < this->tiles[i].size(); j++)
		{
			delete this->tiles[i][j];
			this->tiles[i][j] = nullptr;
		}
	}
}

void Map::addTile(unsigned x, unsigned y, sf::IntRect textureRect, bool damaging)
{
	if (x < this->tiles.size())
	{
		if (y < this->tiles[x].size())
		{
			if (this->tiles[x][y] == nullptr)
			{
				this->tiles[x][y] = new Tile(this->tileSheet, textureRect, damaging);
			}
		}
	}
}

void Map::removeTile(unsigned x, unsigned y)
{
	if (x < this->tiles.size())
	{
		if (y < this->tiles[x].size())
		{
			if (this->tiles[x][y] != nullptr)
			{
				delete this->tiles[x][y];
				this->tiles[x][y] = nullptr;
			}
		}
	}
}

void Map::loadFromFile() {
	std::ifstream inFile("Level1.txt");
	std::string line;
	unsigned x = 0, y = 0;

	while (std::getline(inFile, line)) {
		std::stringstream ss(line);
		char tileChar;
		x = 0; // Reset x position for each new line

		while (ss >> tileChar) {
			switch (tileChar) {
			case WALL:
				this->tileSheet = wallTexture;
				this->addTile(x, y, sf::IntRect(0, 0, tileSize, tileSize), false);
				break;
			case CAT:
				this->tileSheet = catTexture;
				this->addTile(x, y, sf::IntRect(0, 0, tileSize, tileSize), false);
				break;
			case CHEESE:
				this->tileSheet = cheeseTexture;
				this->addTile(x, y, sf::IntRect(0, 0, tileSize, tileSize), false);
				break;
			case MOUSE:
				this->tileSheet = mouseTexture;
				this->addTile(x, y, sf::IntRect(0, 0, tileSize, tileSize), false);
				break;
			case DOOR:
				this->tileSheet = doorTexture;
				this->addTile(x, y, sf::IntRect(0, 0, tileSize, tileSize), false);
				break;
			case KEY:
				this->tileSheet = keyTexture;
				this->addTile(x, y, sf::IntRect(0, 0, tileSize, tileSize), false);
				break;
			case GIFT:
				this->tileSheet = giftTexture;
				this->addTile(x, y, sf::IntRect(0, 0, tileSize, tileSize), false);
				break;
			}
			x++;
		}
		y++;
	}
}

void Map::update()
{
	for (int i = 0; i < this->tiles.size(); i++)
	{
		for (int j = 0; j < this->tiles[i].size(); j++)
		{
			if (this->tiles[i][j] != nullptr)
			{
				this->tiles[i][j]->update();
			}
		}
	}
}

void Map::render(sf::RenderTarget& target)
{
	for (int i = 0; i < this->tiles.size(); i++)
	{
		for (int j = 0; j < this->tiles[i].size(); j++)
		{
			if (this->tiles[i][j] != nullptr)
			{
				this->tiles[i][j]->render(target);
			}
		}
	}
}
