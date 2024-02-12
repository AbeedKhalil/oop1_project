#pragma once

#include "Objects.h"

class Door : public Objects 
{
public:
    Door();
    virtual ~Door();

protected:
    void initTexture() override;
};
