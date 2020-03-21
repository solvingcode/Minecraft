#pragma once
#include "core/camera.h"
#include "vertex/vertex-array.h"
#include "vertex/index-buffer.h"
#include "shader/basic-shader.h"
#include "texture/atlas-texture.h"
#include "world/chunk/mesh.h"

class Chunk;

class ChunkRenderer{
public:
    ChunkRenderer();
    ~ChunkRenderer();
    void Add(Chunk* chunk);
    void Render(Camera &camera, float time);
    void RenderChunk(Camera &camera, Chunk* chunk, Mesh& mesh);
    void Draw(const VertexArray &va, const IndexBuffer &ib) const;
private:
    std::vector<Chunk*> m_Chunks;
    BasicShader m_Shader;
    AtlasTexture m_Texture;
};