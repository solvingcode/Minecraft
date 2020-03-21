#include "mesh.h"

Mesh::Mesh(Entity& model): m_Model(model){
    m_Vb = nullptr;
    m_Layout = nullptr;
    m_Ib = nullptr;
    m_Va = nullptr;
}

Mesh::~Mesh(){
    if(m_Vb != nullptr){
        delete m_Vb;
    }
    if(m_Layout != nullptr){
        delete m_Layout;
    }
    if(m_Ib != nullptr){
        delete m_Ib;
    }
    if(m_Va != nullptr){
        delete m_Va;
    }
}

void Mesh::UpdateVBO(){
    LogTrace("Updating Mesh VBO ...\n");
    if(m_Vb != nullptr){
        delete m_Vb;
    }
    if(m_Layout != nullptr){
        delete m_Layout;
    }
    if(m_Ib != nullptr){
        delete m_Ib;
    }
    if(m_Va != nullptr){
        delete m_Va;
    }
    if(m_Vertices.size() > 0){
        m_Ib = new IndexBuffer(m_Indices.data(), m_Indices.size());
        m_Vb = new VertexBuffer(m_Vertices.data(), sizeof(float) * m_Vertices.size());
        m_Layout = new VertexBufferLayout();
        m_Layout->AddAttribute<float>(3);
        m_Layout->AddAttribute<float>(2);
        m_Layout->AddAttribute<float>(1);
        m_Va = new VertexArray();
        m_Va->AddBuffer(*(m_Vb), *(m_Layout));
    }
}

void Mesh::AddFace(std::array<float, 12>& blockFace, std::array<VectorXY, 4>& texCoords, glm::vec3& position, float light){
    int nbElementPerLayout = 6;
    int countVertices = m_Vertices.size()/nbElementPerLayout;
    for(int i = 0; i < blockFace.size(); i+=3){
        m_Vertices.push_back((float)position.x + blockFace[i]);
        m_Vertices.push_back((float)position.y + blockFace[i+1]);
        m_Vertices.push_back((float)position.z + blockFace[i+2]);
        m_Vertices.push_back(texCoords[i/3].x);
        m_Vertices.push_back(texCoords[i/3].y);
        m_Vertices.push_back(light);
    }
    m_Indices.push_back(countVertices);
    m_Indices.push_back(countVertices + 1);
    m_Indices.push_back(countVertices + 2);
    m_Indices.push_back(countVertices + 2);
    m_Indices.push_back(countVertices + 3);
    m_Indices.push_back(countVertices);
}

void Mesh::DeleteMeshes(){
    m_Vertices.clear();
    m_Indices.clear();
}

std::vector<unsigned int> Mesh::GetIndices(){
    return m_Indices;
}

std::vector<float> Mesh::GetVertices(){
    return m_Vertices;
}

VertexBuffer* Mesh::GetVBO(){
    return m_Vb;
}

IndexBuffer* Mesh::GetIBO(){
    return m_Ib;
}

VertexArray* Mesh::GetVAO(){
    return m_Va;
}

VertexBufferLayout* Mesh::GetLayout(){
    return m_Layout;
}