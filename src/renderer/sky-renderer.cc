#include "sky-renderer.h"

SkyRenderer::SkyRenderer()
: m_Skybox(glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(0,0,0), GetCubeVertices(500.0), GetCubeIndices())
, m_Stars(glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(0,0,0), GetCubeVertices(400.0), GetCubeIndices())
, m_Sun(glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(0,0,0), GetRectVerticesByBlock(40.0, -390, BlockType::Sun), GetRectIndices())
, m_Moon(glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(0,0,0), GetRectVerticesByBlock(40.0, -390, BlockType::Moon), GetRectIndices())
{}

SkyRenderer::~SkyRenderer(){
    LogTrace("Destructing SkyRenderer...\n");
}

std::vector<unsigned int> SkyRenderer::GetCubeIndices(){
    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };
    return indices;
}

std::vector<unsigned int> SkyRenderer::GetRectIndices(){
    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 0
    };
    return indices;
}

std::vector<float> SkyRenderer::GetCubeVertices(const float SIZE){ 
    std::vector<float> vertices = {
        -SIZE, -SIZE, -SIZE,  0.0f, 0.0f, 1.0f,
        SIZE, -SIZE, -SIZE,  1.0f, 0.0f, 1.0f,
        SIZE,  SIZE, -SIZE,  1.0f, 1.0f, 1.0f,
        -SIZE,  SIZE, -SIZE,  0.0f, 1.0f, 1.0f,

        -SIZE, -SIZE,  SIZE,  0.0f, 0.0f, 1.0f,
        SIZE, -SIZE,  SIZE,  1.0f, 0.0f, 1.0f,
        SIZE,  SIZE,  SIZE,  1.0f, 1.0f, 1.0f,
        -SIZE,  SIZE,  SIZE,  0.0f, 1.0f, 1.0f,

        -SIZE,  SIZE,  SIZE,  1.0f, 1.0f, 1.0f,
        -SIZE,  SIZE, -SIZE,  0.0f, 1.0f, 1.0f,
        -SIZE, -SIZE, -SIZE,  0.0f, 0.0f, 1.0f,
        -SIZE, -SIZE,  SIZE,  1.0f, 0.0f, 1.0f,

        SIZE,  SIZE,  SIZE,  0.0f, 1.0f, 1.0f,
        SIZE,  SIZE, -SIZE,  1.0f, 1.0f, 1.0f,
        SIZE, -SIZE, -SIZE,  1.0f, 0.0f, 1.0f,
        SIZE, -SIZE,  SIZE,  0.0f, 0.0f, 1.0f,

        -SIZE, -SIZE, -SIZE,  0.0f, 1.0f, 1.0f,
        SIZE, -SIZE, -SIZE,  1.0f, 1.0f, 1.0f,
        SIZE, -SIZE,  SIZE,  1.0f, 0.0f, 1.0f,
        -SIZE, -SIZE,  SIZE,  0.0f, 0.0f, 1.0f,

        -SIZE,  SIZE, -SIZE,  0.0f, 1.0f, 1.0f,
        SIZE,  SIZE, -SIZE,  1.0f, 1.0f, 1.0f,
        SIZE,  SIZE,  SIZE,  1.0f, 0.0f, 1.0f,
        -SIZE,  SIZE,  SIZE,  0.0f, 0.0f, 1.0f
    };
    return vertices;
}

//@TODO : improve getting texCoords from BlockBase
std::vector<float> SkyRenderer::GetRectVerticesByBlock(const float SIZE, const float DEPTHZ, const BlockType TYPE){ 
    BlockProps SunProps = BlockBase::Get()->GetBlockProps(TYPE);
    BlockTex texCoords = SunProps.m_TexCoords;
    std::vector<float> vertices = {
        -SIZE, -SIZE, DEPTHZ,  texCoords.front[0].x, texCoords.front[0].y, 1.0f,
        SIZE, -SIZE, DEPTHZ,  texCoords.front[1].x, texCoords.front[1].y, 1.0f,
        SIZE,  SIZE, DEPTHZ,  texCoords.front[2].x, texCoords.front[2].y, 1.0f,
        -SIZE,  SIZE, DEPTHZ,  texCoords.front[3].x, texCoords.front[3].y, 1.0f
    };
    return vertices;
}

void SkyRenderer::Render(Camera &camera, float time){
    m_Skybox.Render(camera, time, m_Shader, m_Texture, false);
    m_Sun.Render(camera, time, m_SunShader, m_AtlasTexture, true);
    m_Moon.Render(camera, time, m_MoonShader, m_AtlasTexture, true);
    m_Stars.Render(camera, time, m_StarsShader, m_StarsTexture, true);
}