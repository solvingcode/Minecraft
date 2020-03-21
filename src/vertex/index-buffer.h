#pragma once

#include "utils/log.h"

class IndexBuffer{
    
    unsigned int u_ID;
    unsigned int m_Count;

public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;
    unsigned int GetCount() const;
};