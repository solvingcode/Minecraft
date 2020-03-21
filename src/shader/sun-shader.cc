#include "sun-shader.h"

SunShader::SunShader(): Shader("res/shaders/sun.shader"){
    Bind();
    SetUniform1i("uTexture", 0);
}

SunShader::~SunShader(){
    LogTrace("Destructing SunShader %d...\n", u_ID);
}