#include "index-buffer.h"
#include "renderer/renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : m_Count(count){
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));
    CallGL(glGenBuffers(1, &u_ID));
    CallGL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, u_ID));
    CallGL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

void IndexBuffer::Bind() const {
    CallGL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, u_ID));
}

void IndexBuffer::Unbind() const {
    CallGL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

IndexBuffer::~IndexBuffer(){
    LogTrace("Destructing IndexBuffer %d...\n", u_ID);
    CallGL(glDeleteBuffers(1, &u_ID));
}

unsigned int IndexBuffer::GetCount() const{
    return m_Count;
}