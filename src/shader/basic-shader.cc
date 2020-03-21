#include "basic-shader.h"

BasicShader::BasicShader(): Shader("res/shaders/basic.shader"){
    Bind();
    SetUniform1i("uTexture", 0);
}

BasicShader::~BasicShader(){
    LogTrace("Destructing BasicShader %d...\n", u_ID);
}