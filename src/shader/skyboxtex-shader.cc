#include "skyboxtex-shader.h"

SkyBoxTexShader::SkyBoxTexShader(): Shader("res/shaders/skyboxtex.shader"){
    Bind();
    SetUniform1i("uTexture", 0);
}

SkyBoxTexShader::~SkyBoxTexShader(){
    LogTrace("Destructing SkyBoxTexShader %d...\n", u_ID);
}