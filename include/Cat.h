#pragma once

#include "Objects.h"

class Cat : public Objects
{
public:
    Cat();
    virtual ~Cat();

protected:
    void initTexture() override;
};
