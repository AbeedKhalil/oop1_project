#include "Map.h"

Map::Map()
{
	this->tileSheet = nullptr;
	this->tileSize = 0;
}

Map::Map(unsigned width, unsigned height, sf::Texture* tileSheet, unsigned tileSize)
{
	this->tileSheet = tileSheet;
	this->tileSize = tileSize;

	this->tiles.resize(width);
	for (int i = 0; i < tiles.size(); i++)
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

void Map::addTile(unsigned x, unsigned y)
{
	if (x < this->tiles.size())
	{
		if (y < this->tiles[x].size())
		{
			if (this->tiles[x][y] == nullptr)
			{
				this->tiles[x][y] = new Tile(this->tileSheet, sf::IntRect(0, 0, this->tileSize, this->tileSize), false);
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
