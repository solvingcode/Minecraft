#include "underwater-renderer.h"

UnderWaterRenderer::UnderWaterRenderer()
: m_Model(glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(0,0,0), GetRectVertices(1.0), GetRectIndices())
{}

UnderWaterRenderer::~UnderWaterRenderer(){
    LogTrace("Destructing UnderWaterRenderer...\n");
}

std::vector<unsigned int> UnderWaterRenderer::GetRectIndices(){
    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 0
    };
    return indices;
}

//@TODO : improve getting texCoords from BlockBase
std::vector<float> UnderWaterRenderer::GetRectVertices(const float SIZE){
    std::vector<float> vertices = {
        -SIZE, -SIZE, 0.0f,  0.0f, 0.0f, 1.0f,
        SIZE, -SIZE, 0.0f,  0.0f, 0.0f, 1.0f,
        SIZE,  SIZE, 0.0f,  0.0f, 0.0f, 1.0f,
        -SIZE,  SIZE, 0.0f,  0.0f, 0.0f, 1.0f
    };
    return vertices;
}

void UnderWaterRenderer::Render(Camera &camera, float time){
    m_Model.Render(camera, time, m_Shader, true);
}