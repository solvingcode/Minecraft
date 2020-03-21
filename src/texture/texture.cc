#include "texture.h"
#include "stb_image/stb_image.h"

Texture::Texture(): u_ID(0), m_LocalBuffer(nullptr), m_Width(0), m_Height(0){
}

Texture::~Texture(){
    LogTrace("Destructing Texture %d...\n", u_ID);
    CallGL(glDeleteTextures(1, &u_ID));
}

void Texture::Load(std::string filepath, bool flip){
    if(flip){
        stbi_set_flip_vertically_on_load(1);
    }
    m_LocalBuffer = stbi_load(filepath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

    if(!m_LocalBuffer){
        printf("ERROR while reading image %s\n", filepath.c_str());
        exit(EXIT_FAILURE);
    }
}

void Texture::Unload(){
    if(m_LocalBuffer){
        stbi_image_free(m_LocalBuffer);
    }
}