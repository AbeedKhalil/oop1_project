#include "Heart.h"

Heart::Heart()
{
	initTexture();
	initSprite();
}

void Heart::initTexture()
{
	// Use TextureManager to get the texture instead of loading it directly
	m_texture = TextureManager::getInstance().getTexture("Heart.png");
}
