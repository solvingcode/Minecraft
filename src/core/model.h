#pragma once
#include <vector>
#include "vertex/vertex-array.h"
#include "vertex/index-buffer.h"
#include "core/entity.h"
#include "core/camera.h"
#include "shader/shader.h"
#include "texture/texture.h"

class Model : public Entity{
public:
    Model(glm::vec3 position, glm::vec3 rotation, glm::vec3 velocity, std::vector<float> vertices, std::vector<unsigned int> indices);
    Model();
    ~Model();
    VertexBuffer& GetVBO();
    IndexBuffer& GetIBO();
    VertexArray& GetVAO();
    VertexBufferLayout& GetLayout();
    void Render(Camera& camera, float time, Shader& shader, Texture& texture, const bool blend);
    void Render(Camera& camera, float time, Shader& shader, const bool blend);
    void Draw(const VertexArray &va, const IndexBuffer &ib);
private:
    VertexBuffer m_Vb;
    IndexBuffer m_Ib;
    VertexArray m_Va;
    VertexBufferLayout m_Layout;
};