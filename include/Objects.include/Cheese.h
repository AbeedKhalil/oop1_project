#pragma once

#include "Objects.h"

class Cheese : public Objects {
public:
    Cheese();
    virtual ~Cheese() = default; // Use compiler-generated destructor

protected:
    void initTexture() override;
};