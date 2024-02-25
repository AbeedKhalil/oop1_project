#include "Key.h"

Key::Key()
{
    initTexture();
    initSprite();
}

void Key::initTexture() {
    // Use TextureManager to get the texture instead of loading it directly
    m_texture = TextureManager::getInstance().getTexture("Key.png");
}