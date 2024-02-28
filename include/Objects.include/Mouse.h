#pragma once

#include "MovingObjects.h"
#include "TextureManager.h"

class Mouse : public MovingObjects
{
public:
    Mouse();
    virtual ~Mouse() = default; // Use compiler-generated destructor

    void moveMouse(std::vector<std::shared_ptr<Objects>> movingOjects, std::vector<std::shared_ptr<Objects>> objects, float moveX, float moveY, Score score);

protected:
    void initTexture() override;
};