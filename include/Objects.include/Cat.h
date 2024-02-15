#pragma once

#include "Objects.h"

class Cat : public Objects {
public:
    Cat();
    virtual ~Cat() = default; // Use compiler-generated destructor

protected:
    void initTexture() override;
};