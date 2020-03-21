#pragma once

#include "utils/log.h"
#include <GL/glew.h>

class VertexBuffer{
    
    unsigned int u_ID;

public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
};