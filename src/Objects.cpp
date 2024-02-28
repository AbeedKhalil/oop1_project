#include "Objects.h"

Objects::Objects(float size)
    : m_size(size), m_visible(true) {}

sf::Vector2f Objects::getPosition() const {
    return m_sprite.getPosition();
}

sf::Sprite Objects::getSprite() const {
    return m_sprite;
}

sf::FloatRect Objects::getBounds() const {
    return m_sprite.getGlobalBounds();
}

void Objects::setPosition(float posX, float posY) {
    m_sprite.setPosition(posX, posY);
}

bool Objects::isVisible() const
{
    return m_visible;
}

void Objects::setVisible(bool Visible)
{
    this->m_visible = Visible;
}

void Objects::render(sf::RenderTarget& target) const {
    target.draw(m_sprite);
}

void Objects::initSprite() {
    m_sprite.setTexture(m_texture);

    // Calculate scale factors to adjust the sprite size
    sf::Vector2u textureSize = m_texture.getSize();
    float scaleX = m_size / static_cast<float>(textureSize.x);
    float scaleY = m_size / static_cast<float>(textureSize.y);

    m_sprite.setScale(scaleX, scaleY);
}
