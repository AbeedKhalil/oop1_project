#include "AddTime.h"

AddTime::AddTime()
{
	initTexture();
	initSprite();
}

void AddTime::initTexture()
{
	// Use TextureManager to get the texture instead of loading it directly
	m_texture = TextureManager::getInstance().getTexture("GiftAddTime.png");
}