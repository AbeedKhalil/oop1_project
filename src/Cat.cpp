#include "Cat.h"

Cat::Cat()
{
    this->movementSpeed = 5.f;
    initTexture();
    initSprite();
}

Cat::~Cat()
{
}

void Cat::initTexture()
{
    if (!this->texture.loadFromFile("SmartCat.png"))
    {
        std::cout << "ERROR::CAT::INITTEXTURE::could not load texture file.\n";
    }
}