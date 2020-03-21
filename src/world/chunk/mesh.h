#pragma once

#include <vector>
#include <iostream>
#include "vertex/vertex-array.h"
#include "vertex/index-buffer.h"
#include "maths/vector.h"
#include "maths/glm.h"
#include <array>
#include "core/entity.h"

class Mesh{
public:
    Mesh(Entity& model);
    ~Mesh();
    std::vector<unsigned int> GetIndices();
    std::vector<float> GetVertices();
    VertexBuffer* GetVBO();
    IndexBuffer* GetIBO();
    VertexArray* GetVAO();
    VertexBufferLayout* GetLayout();
    void AddFace(std::array<float, 12>& blockFace, std::array<VectorXY, 4>& texCoords, glm::vec3& position, float light);
    void UpdateVBO();
    void DeleteMeshes();
private:
    Entity& m_Model;
    std::vector<float> m_Vertices;
    std::vector<unsigned int> m_Indices;
    VertexBuffer* m_Vb = nullptr;
    IndexBuffer* m_Ib = nullptr;
    VertexArray* m_Va = nullptr;
    VertexBufferLayout* m_Layout = nullptr;
};