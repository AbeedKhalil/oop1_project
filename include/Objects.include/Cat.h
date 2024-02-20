#pragma once

#include "MovingObjects.h"

class Cat : public MovingObjects {
public:
    Cat();
    virtual ~Cat() = default; // Use compiler-generated destructor

protected:
    void initTexture() override;
};