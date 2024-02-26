#pragma once

#include "Objects.h"
#include "TextureManager.h"

class AddTime : public Objects {
public:
    AddTime();
    virtual ~AddTime() = default; // Use compiler-generated destructor

protected:
    void initTexture() override;
};