#pragma once

#include "Objects.h"

class Cheese : public Objects {
public:
    Cheese();
    virtual ~Cheese();

protected:
    void initTexture() override;
};