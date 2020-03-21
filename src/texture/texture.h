#pragma once

#include "utils/log.h"

class Texture{
protected:
    unsigned int u_ID;
    std::string m_Filepath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;

public:
    Texture();
    ~Texture();

    void Load(std::string filepath, bool flip = false);
    void Unload();
    virtual void Bind(unsigned int slot = 0) const = 0;
    virtual void Unbind() const = 0;

    int GetWidth() const;
    int GetHeight() const;
};