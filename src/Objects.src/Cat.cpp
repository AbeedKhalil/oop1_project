#include "Cat.h"

Cat::Cat() : MovingObjects(2.f) // Initialize base class members with constructor initializer list
{
    initTexture();
    initSprite();
}

void Cat::moveCat(std::vector<std::shared_ptr<Objects>> objects, sf::Vector2f mousePos, sf::Vector2f catPos, Score score)
{
    static sf::Vector2f velocity(0, 0); // Current velocity of the cat
    const float accelerationRate = 0.1f; // Acceleration rate
    const float maxSpeed = getMovementSpeed(); // Max speed based on the cat's movement speed
    const float decelerationRate = 0.1f; // Deceleration rate when changing direction or stopping

    // Calculate normalized direction vector from cat to mouse
    sf::Vector2f direction = mousePos - catPos;
    float magnitude = std::hypot(direction.x, direction.y);
    if (magnitude > 0) {
        direction /= magnitude; // Normalize the direction vector
    }

    // Apply acceleration
    if (magnitude > 0) {
        velocity += direction * accelerationRate;
        // Clamp velocity to maxSpeed
        float currentSpeed = std::hypot(velocity.x, velocity.y);
        if (currentSpeed > maxSpeed) {
            velocity *= maxSpeed / currentSpeed;
        }
    }
    else {
        // Apply deceleration when the cat is not moving towards the mouse
        float currentSpeed = std::hypot(velocity.x, velocity.y);
        if (currentSpeed > 0) {
            sf::Vector2f deceleration = -velocity / currentSpeed * decelerationRate;
            velocity += deceleration;
            // Prevent overshooting to the opposite direction
            if (std::hypot(velocity.x, velocity.y) < decelerationRate) {
                velocity = sf::Vector2f(0, 0);
            }
        }
    }

    // Attempt movement with new velocity
    bool canMoveX = !checkCollision(objects, this, velocity.x, 0, score);
    bool canMoveY = !checkCollision(objects, this, 0, velocity.y, score);

    if (canMoveX) {
        this->move(velocity.x, 0);
    }
    if (canMoveY) {
        this->move(0, velocity.y);
    }
    else if (!canMoveX && !canMoveY) {
        // If direct movement is blocked, try alternative directions with current velocity
        for (const auto& altDir : alternativeDirections) {
            if (!checkCollision(objects, this, altDir.x * velocity.x, altDir.y * velocity.y, score)) {
                this->move(altDir.x * velocity.x, altDir.y * velocity.y);
                break;
            }
        }
    }
}

void Cat::initTexture()
{
    if (!m_texture.loadFromFile("SmartCat.png")) {
        // Error handling
        std::cerr << "ERROR::CAT::Could not load texture file." << std::endl;
    }
}