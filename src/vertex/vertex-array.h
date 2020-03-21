#pragma once

#include "utils/log.h"
#include "vertex-buffer-layout.h"
#include "vertex-buffer.h"

class VertexArray{
    unsigned int u_ID;
public:

    VertexArray();
    ~VertexArray();

    unsigned int getId(){ return u_ID; }

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    void Bind() const;
    void Unbind() const;

};