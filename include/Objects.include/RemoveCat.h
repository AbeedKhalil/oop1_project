#pragma once

#include "Objects.h"

class RemoveCat : public Objects {
public:
    RemoveCat();
    virtual ~RemoveCat();

protected:
    void initTexture() override;
};
