#pragma once

#include "Consts.h"

class Tile
{
private:
	const bool damaging;

public:
	sf::Sprite sprite;
	Tile(sf::Texture* textureSheet, sf::IntRect textureRect, bool damaging = false);
	const sf::FloatRect getGloubalBounds() const;
	void update();
	void render(sf::RenderTarget& target) const;
};