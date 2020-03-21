#include "vertex-array.h"

VertexArray::VertexArray(){
    CallGL(glGenVertexArrays(1, &u_ID));
    CallGL(glBindVertexArray(u_ID));
}

VertexArray::~VertexArray(){
    LogTrace("Destructing VertexArray %d...\n", u_ID);
    CallGL(glDeleteVertexArrays(1, &u_ID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout){
    Bind();
    vb.Bind();
    std::vector<VertextBufferLayoutElement> elements = layout.GetElements();
    unsigned int offset = 0;
    for(int i = 0; i < elements.size(); i++){
        const VertextBufferLayoutElement element = elements[i];
        CallGL(glEnableVertexAttribArray(i));
        CallGL(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
        offset += element.count * VertextBufferLayoutElement::GetSize(element.type);
    }
}

void VertexArray::Bind() const {
    CallGL(glBindVertexArray(u_ID));
}

void VertexArray::Unbind() const {
    CallGL(glBindVertexArray(0));
}