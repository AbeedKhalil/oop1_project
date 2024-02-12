#include "Objects.h"

Objects::Objects(float posX, float posY)
{
    this->movementSpeed = 0.f;
    this->sprite.setPosition(posX, posY);
}

Objects::~Objects()
{
}

void Objects::move(const float dirX, const float dirY) 
{
    this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

sf::Vector2f Objects::getPosition() const
{
    return this->sprite.getPosition();
}

float Objects::getMovementSpeed() const
{
    return this->movementSpeed;
}

void Objects::update() 
{
}

void Objects::render(sf::RenderTarget& target) const
{
    target.draw(this->sprite);
}

void Objects::initSprite()
{
    this->sprite.setTexture(this->texture);

    // Get the original size of the texture
    sf::Vector2u textureSize = this->texture.getSize();

    // Calculate the scale factors
    float scaleX = 60.f / textureSize.x; // Desired width / original width
    float scaleY = 60.f / textureSize.y; // Desired height / original height

    // Set the sprite's scale to adjust its size
    this->sprite.setScale(scaleX, scaleY);
}
