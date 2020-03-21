#include "cloud-shader.h"

CloudShader::CloudShader(): Shader("res/shaders/cloud.shader"){
    Bind();
    SetUniform1i("uTexture", 0);
}

CloudShader::~CloudShader(){
    LogTrace("Destructing CloudShader %d...\n", u_ID);
}