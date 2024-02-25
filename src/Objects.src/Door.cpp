#include "Door.h"

Door::Door()
{
    this->m_size = 60.f;
    initTexture();
    initSprite();
}

void Door::initTexture() {
    // Use TextureManager to get the texture instead of loading it directly
    m_texture = TextureManager::getInstance().getTexture("Door.png");
}