#include "Mouse.h"

Mouse::Mouse()
{
    this->movementSpeed = 5.f;
    initTexture();
    initSprite();
}

Mouse::~Mouse()
{
}

void Mouse::initTexture()
{
    if (!this->texture.loadFromFile("Mouse.png"))
    {
        std::cout << "ERROR::MOUSE::INITTEXTURE::could not load texture file.\n";
    }
}
