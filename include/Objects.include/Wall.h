#pragma once

#include "Objects.h"

class Wall : public Objects {
public:
    Wall();
    virtual ~Wall();

protected:
    void initTexture() override;
};