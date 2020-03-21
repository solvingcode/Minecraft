#include "stars-shader.h"

StarsShader::StarsShader(): Shader("res/shaders/stars.shader"){
    Bind();
    SetUniform1i("uTexture", 0);
}

StarsShader::~StarsShader(){
    LogTrace("Destructing StarsShader %d...\n", u_ID);
}