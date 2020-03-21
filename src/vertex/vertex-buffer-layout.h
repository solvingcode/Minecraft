#pragma once
#include "utils/log.h"
#include <GL/glew.h>
#include <vector>

struct VertextBufferLayoutElement
{
    unsigned int type;
    unsigned int count;
    GLuint normalized;

    static unsigned int GetSize(unsigned int type){
        switch (type)
        {
        case GL_FLOAT:
            return 4;
            break;
        case GL_UNSIGNED_INT:
            return 4;
            break;
        case GL_UNSIGNED_BYTE:
            return 1;
            break;
        }
        ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout
{
    std::vector<VertextBufferLayoutElement> m_Elements;
    unsigned int m_Stride;

public:
    VertexBufferLayout();
    ~VertexBufferLayout();

    template <typename T>
    void AddAttribute(unsigned int count);
    
    std::vector<VertextBufferLayoutElement> GetElements() const;
    unsigned int GetStride() const;
};