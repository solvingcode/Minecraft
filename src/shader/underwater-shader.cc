#include "underwater-shader.h"

UnderWaterShader::UnderWaterShader(): Shader("res/shaders/underwater.shader"){
    Bind();
}

UnderWaterShader::~UnderWaterShader(){
    LogTrace("Destructing UnderWaterShader %d...\n", u_ID);
}