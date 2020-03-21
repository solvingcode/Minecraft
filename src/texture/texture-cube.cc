#include "texture-cube.h"

TextureCube::TextureCube(std::string filepath[6]){
    CallGL(glGenTextures(1, &u_ID));
    CallGL(glBindTexture(GL_TEXTURE_CUBE_MAP, u_ID));

    CallGL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    CallGL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    CallGL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    CallGL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    for (unsigned int i = 0; i < 6; i++)
    {
        Load(filepath[i]);
        CallGL(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
        Unload();
    }
}

void TextureCube::Bind(unsigned int slot) const{
    CallGL(glActiveTexture(GL_TEXTURE0 + slot));
    CallGL(glBindTexture(GL_TEXTURE_CUBE_MAP, u_ID));
}

void TextureCube::Unbind() const{
    CallGL(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}