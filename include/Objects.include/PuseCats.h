#pragma once

#include "Objects.h"
#include "TextureManager.h"

class PuseCats : public Objects {
public:
    PuseCats();
    virtual ~PuseCats() = default; // Use compiler-generated destructor

protected:
    void initTexture() override;
};