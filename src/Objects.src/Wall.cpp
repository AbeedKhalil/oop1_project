#include "Wall.h"

Wall::Wall()
{
    this->m_size = 60.f;
    initTexture();
    initSprite();
}

void Wall::initTexture() 
{
    // Use TextureManager to get the texture instead of loading it directly
    m_texture = TextureManager::getInstance().getTexture("Wall.png");
}