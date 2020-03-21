#include "renderer.h"

void ClearLogs(){
    while(glGetError());   
}

bool LogCall(std::string function, std::string file, int line){
    if(unsigned int error = glGetError()){
        printf("[OpenGL Error] : (%d, %s), Call : %s in %s:%d\n", error, gluErrorString(error), function.c_str(), file.c_str(), line);
        //std::cout << "[OpenGL Error] : (" << error << "), Call : " << function << " in " << file << ":" << line << std::endl;
        return false;
    }   
    return true;
}

void Renderer::Clear() const{
    CallGL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}


void Renderer::Render(Camera &camera, float time, bool isUnderWater){
    m_ChunkRenderer.Render(camera, time);
    m_SkyRenderer.Render(camera, time);
    m_WaterRenderer.Render(camera, time);
    m_CloudRenderer.Render(camera, time);
    if(isUnderWater){
        m_UnderWaterRenderer.Render(camera, time);
    }
}

//@TODO : Optimize switching between renderers
void Renderer::DrawChunk(Chunk* chunk){
    if(chunk->GetMeshes().m_Solid.GetVertices().size() > 0){
        m_ChunkRenderer.Add(chunk);
    }
    if(chunk->GetMeshes().m_Water.GetVertices().size() > 0){
        m_WaterRenderer.Add(chunk);
    }
    if(chunk->GetMeshes().m_Cloud.GetVertices().size() > 0){
        m_CloudRenderer.Add(chunk);
    }
}

Renderer::~Renderer(){
    LogTrace("Destructing renderer...\n");
}
