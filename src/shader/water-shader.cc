#include "water-shader.h"

WaterShader::WaterShader(): Shader("res/shaders/water.shader"){
    Bind();
    SetUniform1i("uTexture", 0);
}

WaterShader::~WaterShader(){
    LogTrace("Destructing WaterShader %d...\n", u_ID);
}