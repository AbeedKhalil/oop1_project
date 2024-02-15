#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Objects {
private:
    // Private methods or members can be added here

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
    virtual void update();
    void render(sf::RenderTarget& target) const;

protected:
    sf::Sprite sprite;
    sf::Texture texture;
    float movementSpeed;
    float size;

    // Initialization functions
    virtual void initTexture() = 0;
    virtual void initSprite();
};
