#pragma once

#include <GL/glew.h>
#include <iostream>
#include <vector>
#include "maths/glm.h"
#include <algorithm>
#include "world/chunk/chunk.h"
#include "chunk-renderer.h"
#include "water-renderer.h"
#include "cloud-renderer.h"
#include "sky-renderer.h"
#include "underwater-renderer.h"

class Chunk;

class Renderer{
public:
    Renderer() = default;
    ~Renderer();
    void Render(Camera &camera, float time, bool isUnderWater);
    void Clear() const;
    void DrawChunk(Chunk* chunk);
private:
    SkyRenderer m_SkyRenderer;
    ChunkRenderer m_ChunkRenderer;
    WaterRenderer m_WaterRenderer;
    CloudRenderer m_CloudRenderer;
    UnderWaterRenderer m_UnderWaterRenderer;
};
