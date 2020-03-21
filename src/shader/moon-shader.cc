#include "moon-shader.h"

MoonShader::MoonShader(): Shader("res/shaders/moon.shader"){
    Bind();
    SetUniform1i("uTexture", 0);
}

MoonShader::~MoonShader(){
    LogTrace("Destructing MoonShader %d...\n", u_ID);
}