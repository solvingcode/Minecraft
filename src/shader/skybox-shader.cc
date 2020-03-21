#include "skybox-shader.h"

SkyBoxShader::SkyBoxShader(): Shader("res/shaders/skybox.shader"){
    Bind();
}

SkyBoxShader::~SkyBoxShader(){
    LogTrace("Destructing SkyBoxShader %d...\n", u_ID);
}