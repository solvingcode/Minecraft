#include "water-renderer.h"
#include "world/chunk/chunk.h"

WaterRenderer::WaterRenderer(){}

void WaterRenderer::Draw(const VertexArray &va, const IndexBuffer &ib) const{
    va.Bind();
    ib.Bind();
    CallGL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void WaterRenderer::Render(Camera &camera, float time){
    if(m_Chunks.empty()){
        return;
    }
    CallGL(glEnable(GL_BLEND));
    m_Shader.Bind();
    m_Shader.SetUniform1f("uTime", time);
    m_Texture.Bind();
    for(Chunk* chunk : m_Chunks){
        RenderChunk(camera, chunk, chunk->GetMeshes().m_Water);
    }
    m_Chunks.clear();
}
    
void WaterRenderer::RenderChunk(Camera &camera, Chunk* chunk, Mesh& mesh){
    chunk->UpdateVBO();
    glm::mat4 viewMatrix = camera.GetViewMatrix();
    glm::mat4 projMatrix = camera.GetProjectionMatrix();
    glm::mat4 modelMatrix = chunk->GetModelMatrix();
    glm::mat4 MVP = projMatrix * viewMatrix * modelMatrix;
    m_Shader.SetUniformMat4("m_MVP", MVP);
    Draw(*(mesh.GetVAO()), *(mesh.GetIBO()));
}

void WaterRenderer::Add(Chunk* chunk){
    m_Chunks.push_back(chunk);
}

WaterRenderer::~WaterRenderer(){
    LogTrace("Destructing WaterRenderer...\n");
}