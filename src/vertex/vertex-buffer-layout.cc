#include "vertex-buffer-layout.h"

VertexBufferLayout::VertexBufferLayout() : m_Stride(0) {}

VertexBufferLayout::~VertexBufferLayout(){
    LogTrace("Destructing VertexBufferLayout...\n");
}

template <>
void VertexBufferLayout::AddAttribute<float>(unsigned int count)
{
    m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
    m_Stride += VertextBufferLayoutElement::GetSize(GL_FLOAT) * count;
}

template <>
void VertexBufferLayout::AddAttribute<unsigned int>(unsigned int count)
{
    m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
    m_Stride += VertextBufferLayoutElement::GetSize(GL_UNSIGNED_INT) * count;
}

std::vector<VertextBufferLayoutElement> VertexBufferLayout::GetElements() const{
    return m_Elements;
}

unsigned int VertexBufferLayout::GetStride() const{
    return m_Stride;
}