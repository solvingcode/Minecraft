#pragma once
#include "texture.h"

class TextureCube : public Texture{
public:
    TextureCube(std::string filepath[6]);
    void Bind(unsigned int slot = 0) const override;
    void Unbind() const override;
};