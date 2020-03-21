#include "vertex-buffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size){
    CallGL(glGenBuffers(1, &u_ID));
    CallGL(glBindBuffer(GL_ARRAY_BUFFER, u_ID));
    CallGL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void VertexBuffer::Bind() const {
    CallGL(glBindBuffer(GL_ARRAY_BUFFER, u_ID));
}

void VertexBuffer::Unbind() const {
    CallGL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

VertexBuffer::~VertexBuffer(){
    LogTrace("Destructing VertexBuffer %d...\n", u_ID);
    CallGL(glDeleteBuffers(1, &u_ID));
}