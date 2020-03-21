#include "sky-texture.h"

SkyTexture::SkyTexture(): TextureCube(new std::string[6]{
    "res/textures/sky/sky_side.png", //front
    "res/textures/sky/sky_side.png", //back
    "res/textures/sky/sky_top.png", //top
    "res/textures/sky/sky_bottom.png", //bottom
    "res/textures/sky/sky_side.png", //right
    "res/textures/sky/sky_side.png", //left
}){
}