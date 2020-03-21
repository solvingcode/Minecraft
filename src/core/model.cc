#include "model.h"

Model::Model(
    glm::vec3 position, 
    glm::vec3 rotation, 
    glm::vec3 velocity,
    std::vector<float> vertices, 
    std::vector<unsigned int> indices
) 
: Entity(position, rotation, velocity)
, m_Ib(indices.data(), indices.size())
, m_Vb(vertices.data(), sizeof(float) * vertices.size())
{
    m_Layout.AddAttribute<float>(3);
    m_Layout.AddAttribute<float>(2);
    m_Layout.AddAttribute<float>(1);
    m_Va.AddBuffer(m_Vb, m_Layout);
}

Model::Model(): Model(glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(0,0,0), {}, {}){}

Model::~Model(){
    LogTrace("Destructing Model...\n");
}

VertexBuffer& Model::GetVBO(){
    return m_Vb;
}

IndexBuffer& Model::GetIBO(){
    return m_Ib;
}

VertexBufferLayout& Model::GetLayout(){
    return m_Layout;
}

VertexArray& Model::GetVAO(){
    return m_Va;
}

void Model::Render(Camera& camera, float time, Shader& shader, Texture& texture, const bool blend){
    if(blend){
        CallGL(glEnable(GL_BLEND));
    }else{
        CallGL(glDisable(GL_BLEND));
    }
    shader.Bind();
    glm::mat4 viewMatrixRotation = camera.GetViewMatrixRotation();
    glm::mat4 projMatrix = camera.GetProjectionMatrix();
    glm::mat4 modelMatrix = camera.GetModelMatrix();
    glm::mat4 MVP = projMatrix * viewMatrixRotation;
    shader.SetUniformMat4("m_MVP", MVP);
    shader.SetUniform1f("uTime", time);
    texture.Bind();
    Draw(GetVAO(), GetIBO());
}

void Model::Render(Camera& camera, float time, Shader& shader, const bool blend){
    if(blend){
        CallGL(glEnable(GL_BLEND));
    }else{
        CallGL(glDisable(GL_BLEND));
    }
    shader.Bind();
    glm::mat4 viewMatrixRotation = camera.GetViewMatrixRotation();
    glm::mat4 projMatrix = camera.GetProjectionMatrix();
    glm::mat4 modelMatrix = camera.GetModelMatrix();
    glm::mat4 MVP = projMatrix * viewMatrixRotation;
    shader.SetUniformMat4("m_MVP", MVP);
    shader.SetUniform1f("uTime", time);
    Draw(GetVAO(), GetIBO());
}

void Model::Draw(const VertexArray &va, const IndexBuffer &ib){
    va.Bind();
    ib.Bind();
    CallGL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}