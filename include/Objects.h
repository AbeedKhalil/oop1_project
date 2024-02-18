#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Objects {
private:
    bool m_visible;

public:
    // Constructor
    Objects(float movementSpeed = 0.f, float size = 35.f);

    // Virtual Destructor
    virtual ~Objects() = default;

    // Functions
    virtual void move(float dirX, float dirY);
    sf::Vector2f getPosition() const;
    sf::Sprite getSprite() const;
    sf::FloatRect getBounds() const;
    void setPosition(float posX, float posY);
    float getMovementSpeed() const;
    bool isVisible() const;
    void setVisible(bool Visible);
    virtual void update();
    void render(sf::RenderTarget& target) const;

protected:
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    float m_movementSpeed;
    float m_size;

    // Initialization functions
    virtual void initTexture() = 0;
    virtual void initSprite();
};
