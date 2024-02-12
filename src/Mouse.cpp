#include "Mouse.h"

Mouse::Mouse() : Objects(0.f, 100.f)
{
    this->movementSpeed = 3.f;
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
