#include "texture-2d.h"

Texture2d::Texture2d(std::string filepath){
    Load(filepath, true);

    CallGL(glGenTextures(1, &u_ID));
    CallGL(glBindTexture(GL_TEXTURE_2D, u_ID));

    CallGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    CallGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    CallGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    CallGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    CallGL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
    CallGL(glBindTexture(GL_TEXTURE_2D, 0));

    Unload();
}

void Texture2d::Bind(unsigned int slot) const{
    CallGL(glActiveTexture(GL_TEXTURE0 + slot));
    CallGL(glBindTexture(GL_TEXTURE_2D, u_ID));
}

void Texture2d::Unbind() const{
    CallGL(glBindTexture(GL_TEXTURE_2D, 0));
}