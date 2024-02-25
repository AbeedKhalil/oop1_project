#include "RemoveCat.h"

RemoveCat::RemoveCat()
{
    initTexture();
    initSprite();
}

void RemoveCat::initTexture() {
    // Use TextureManager to get the texture instead of loading it directly
    m_texture = TextureManager::getInstance().getTexture("GiftRemoveCat.png");
}