#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Objects {
public:
    // Constructor and Destructor
    Objects();
    virtual ~Objects();

    // Functions
    virtual void move(const float dirX, const float dirY);
    sf::Vector2f getPosition() const;
    void setPosition(float posX, float posY);
    float getMovementSpeed() const;
    virtual void update();
    void render(sf::RenderTarget& target) const;

protected:
    sf::Sprite sprite;
    sf::Texture texture;
    float movementSpeed;

    // Initialization functions
    virtual void initTexture() = 0;
    virtual void initSprite();
};
