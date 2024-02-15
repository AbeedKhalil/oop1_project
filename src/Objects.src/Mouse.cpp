#include "Mouse.h"

Mouse::Mouse() : Objects(2.f, 45.f) // Initialize base class members with constructor initializer list
{
    initTexture();
    initSprite();
}

void Mouse::initTexture()
{
    if (!this->texture.loadFromFile("Mouse.png"))
    {
        // Error handling
        std::cerr << "ERROR::MOUSE::INITTEXTURE::could not load texture file.\n";
    }
}
