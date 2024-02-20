#include "Mouse.h"

Mouse::Mouse() : MovingObjects(2.f) // Initialize base class members with constructor initializer list
{
    initTexture();
    initSprite();
}

void Mouse::initTexture()
{
    if (!this->m_texture.loadFromFile("Mouse.png"))
    {
        // Error handling
        std::cerr << "ERROR::MOUSE::INITTEXTURE::could not load texture file.\n";
    }
}
