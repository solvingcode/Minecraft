#pragma once
#include "texture.h"

class Texture2d : public Texture{
public:
    Texture2d(std::string filepath);
    void Bind(unsigned int slot = 0) const override;
    void Unbind() const override;
};