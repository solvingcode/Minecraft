#include "chunk-renderer.h"
#include "world/chunk/chunk.h"

ChunkRenderer::ChunkRenderer(){}

void ChunkRenderer::Draw(const VertexArray &va, const IndexBuffer &ib) const{
    va.Bind();
    ib.Bind();
    CallGL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void ChunkRenderer::Render(Camera &camera, float time){
    if(m_Chunks.empty()){
        return;
    }
    CallGL(glDisable(GL_BLEND));
    m_Shader.Bind();
    m_Shader.SetUniform1f("uTime", time);
    m_Texture.Bind();
    for(Chunk* chunk : m_Chunks){
        RenderChunk(camera, chunk, chunk->GetMeshes().m_Solid);
    }
    m_Chunks.clear();
}
    
void ChunkRenderer::RenderChunk(Camera &camera, Chunk* chunk, Mesh& mesh){
    chunk->UpdateVBO();
    glm::mat4 viewMatrix = camera.GetViewMatrix();
    glm::mat4 projMatrix = camera.GetProjectionMatrix();
    glm::mat4 modelMatrix = chunk->GetModelMatrix();
    glm::mat4 MVP = projMatrix * viewMatrix * modelMatrix;
    m_Shader.SetUniformMat4("m_MVP", MVP);
    m_Shader.SetUniformMat4("m_M", modelMatrix);
    Draw(*(mesh.GetVAO()), *(mesh.GetIBO()));
}

void ChunkRenderer::Add(Chunk* chunk){
    m_Chunks.push_back(chunk);
}

ChunkRenderer::~ChunkRenderer(){
    LogTrace("Destructing ChunkRenderer...\n");
}