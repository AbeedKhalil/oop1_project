#include "Objects.h"

Objects::Objects(float movementSpeed, float size)
    : movementSpeed(movementSpeed), size(size) {}

void Objects::move(float dirX, float dirY) {
    sprite.move(movementSpeed * dirX, movementSpeed * dirY);
}

sf::Vector2f Objects::getPosition() const {
    return sprite.getPosition();
}

sf::Sprite Objects::getSprite() const {
    return sprite;
}

sf::FloatRect Objects::getBounds() const {
    return sprite.getGlobalBounds();
}

void Objects::setPosition(float posX, float posY) {
    sprite.setPosition(posX, posY);
}

float Objects::getMovementSpeed() const {
    return movementSpeed;
}

void Objects::update() {
    // Empty implementation, meant to be overridden
}

void Objects::render(sf::RenderTarget& target) const {
    target.draw(sprite);
}

void Objects::initSprite() {
    sprite.setTexture(texture);

    // Calculate scale factors to adjust the sprite size
    sf::Vector2u textureSize = texture.getSize();
    float scaleX = size / static_cast<float>(textureSize.x);
    float scaleY = size / static_cast<float>(textureSize.y);

    sprite.setScale(scaleX, scaleY);
}
