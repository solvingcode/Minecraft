#pragma once
#include "vertex/vertex-array.h"
#include "vertex/index-buffer.h"
#include "shader/skyboxtex-shader.h"
#include "shader/stars-shader.h"
#include "shader/sun-shader.h"
#include "shader/moon-shader.h"
#include "texture/sky-texture.h"
#include "texture/stars-texture.h"
#include "texture/atlas-texture.h"
#include "world/block/block-base.h"
#include <vector>
#include "core/camera.h"
#include "core/model.h"
#include <algorithm>

class SkyRenderer{
public:
    SkyRenderer();
    ~SkyRenderer();
    void Render(Camera &camera, float time);
private:
    std::vector<float> GetCubeVertices(const float SIZE);
    std::vector<unsigned int> GetCubeIndices();
    std::vector<float> GetRectVerticesByBlock(const float SIZE, const float DEPTHZ, const BlockType TYPE);
    std::vector<unsigned int> GetRectIndices();
    SkyTexture m_Texture;
    StarsTexture m_StarsTexture;
    AtlasTexture m_AtlasTexture;
    SkyBoxTexShader m_Shader;
    StarsShader m_StarsShader;
    SunShader m_SunShader;
    MoonShader m_MoonShader;
    Model m_Stars;
    Model m_Skybox;
    Model m_Sun;
    Model m_Moon;
};