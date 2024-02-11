#include "Tile.h"

Tile::Tile(sf::Texture* textureSheet, sf::IntRect textureRect, bool damaging) : damaging(damaging)
{
	this->sprite.setTexture(*textureSheet);
	this->sprite.setTextureRect(textureRect);
}

const sf::FloatRect Tile::getGloubalBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Tile::update()
{
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
