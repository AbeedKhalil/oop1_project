#include "Cheese.h"

Cheese::Cheese()
{
    initTexture();
    initSprite(); // Assuming initSprite() is suitable without modifications
}

void Cheese::initTexture() {
    // Use TextureManager to get the texture instead of loading it directly
    m_texture = TextureManager::getInstance().getTexture("Cheese.png");
}