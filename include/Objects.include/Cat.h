#pragma once

#include "MovingObjects.h"

class Cat : public MovingObjects {
public:
    Cat();
    virtual ~Cat() = default; // Use compiler-generated destructor

    std::vector<sf::Vector2f> alternativeDirections = {
    {0, 1},  // Down
    {1, 0},  // Right
    {0, -1}, // Up
    {-1, 0}  // Left
    };

    void moveCat(std::vector<std::shared_ptr<Objects>> objects, sf::Vector2f mousePos, sf::Vector2f catPos, Score score);

protected:
    void initTexture() override;
};