#include "stars-texture.h"

StarsTexture::StarsTexture(): TextureCube(new std::string[6]{
    "res/textures/stars/stars_side.png", //front
    "res/textures/stars/stars_side.png", //back
    "res/textures/stars/stars_side.png", //top
    "res/textures/stars/stars_bottom.png", //bottom
    "res/textures/stars/stars_side.png", //right
    "res/textures/stars/stars_side.png", //left
}){
}