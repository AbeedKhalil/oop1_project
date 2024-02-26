#include "PuseCats.h"

PuseCats::PuseCats()
{
	initTexture();
	initSprite();
}

void PuseCats::initTexture()
{
	// Use TextureManager to get the texture instead of loading it directly
	m_texture = TextureManager::getInstance().getTexture("Puse.png");
}