#pragma once
#include "core/camera.h"
#include "vertex/vertex-array.h"
#include "vertex/index-buffer.h"
#include "shader/cloud-shader.h"
#include "texture/atlas-texture.h"
#include "world/chunk/mesh.h"

class Chunk;

class CloudRenderer{
public:
    CloudRenderer();
    ~CloudRenderer();
    void Add(Chunk* chunk);
    void Render(Camera &camera, float time);
    void RenderChunk(Camera &camera, Chunk* chunk, Mesh& mesh);
    void Draw(const VertexArray &va, const IndexBuffer &ib) const;
private:
    std::vector<Chunk*> m_Chunks;
    CloudShader m_Shader;
    AtlasTexture m_Texture;
};