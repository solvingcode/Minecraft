#pragma once
#include "vertex/vertex-array.h"
#include "vertex/index-buffer.h"
#include "shader/underwater-shader.h"
#include <vector>
#include "core/camera.h"
#include "core/model.h"
#include <algorithm>

class UnderWaterRenderer{
public:
    UnderWaterRenderer();
    ~UnderWaterRenderer();
    void Render(Camera &camera, float time);
private:
    std::vector<float> GetRectVertices(const float SIZE);
    std::vector<unsigned int> GetRectIndices();
    UnderWaterShader m_Shader;
    Model m_Model;
};